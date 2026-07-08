#include "private.h"
#include <kronklab/kronklab.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void run_test(
    struct __kl_funcStruct *current,
    unsigned long *results
)
{
    int pid = fork();
    timestamp now = kl_monotonic();
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
                klError("Test %s:%s aborted (Standard assert failed or abort() called)\n", current->suite, current->name);
            } 
            else if (sign == SIGFPE) {
                klError("Floating point exception (Division by zero) in %s:%s\n", current->suite, current->name);
            } 
            else {
                klError("Test %s:%s killed by signal %d\n", current->suite, current->name, sign);
            }
            ++results[3];
        }  else if (WIFEXITED(wstatus)) {
            int sign = WEXITSTATUS(wstatus);
            if (sign == 0) {
                klGood("Test %s:%s runned successfully. Took %zu ms.\n", current->suite, current->name, kl_monotonic() - now);
                ++results[1];
            } else {
                ++results[2];
            }
        }
    }
}
