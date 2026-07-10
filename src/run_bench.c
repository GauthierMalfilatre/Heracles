#include "private.h"
#include <kronklab/kronklab.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void run_bench(
    struct __kl_funcStruct *current,
    unsigned long *results
)
{
    int pid = fork();
    timestamp now = kl_high_monotonic();
    int wstatus;

    if (pid == -1) {
        klError("Failed to run test %s:%s\n", current->suite, current->name);
        ++results[2];
        return;
    } else if (pid == 0) {
        current->func();
        exit(0);
    } else {
        waitpid(pid, &wstatus, 0);
        if (WIFSIGNALED(wstatus)) {
            int sign = WTERMSIG(wstatus);
            if (sign == SIGSEGV) {
                klError("Segmentation fault while running %s:%s\n", current->suite, current->name);
            } 
            else if (sign == SIGABRT) {
                klError("Bench %s:%s aborted (Standard assert failed or abort() called)\n", current->suite, current->name);
            } 
            else if (sign == SIGFPE) {
                klError("Bench %s:%s: Floating point exception (Division by zero)\n", current->suite, current->name);
            } 
            else {
                klError("Bench %s:%s killed by signal %d\n", current->suite, current->name, sign);
            }
        }  else if (WIFEXITED(wstatus)) {
            int sign = WEXITSTATUS(wstatus);
            if (sign == 0) {
                klGood("Successfully benched %s:%s. Runned in %zu us.\n", current->suite, current->name, kl_high_monotonic() - now);
            } else {
                klError("Bench %s:%s failed.\n", current->suite, current->name);
            }
        }
    }
}
