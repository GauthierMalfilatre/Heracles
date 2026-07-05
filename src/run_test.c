#include "private.h"
#include <heracles/heracles.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void run_test(
    struct __hc_funcStruct *current,
    unsigned long *results
)
{
    int pid = fork();
    timestamp now = hc_monotonic();
    int wstatus;

    if (pid == -1) {
        hcError("Failed to run test %s:%s\n", current->suite, current->name);
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
                hcError("Segmentation fault while running %s:%s\n", current->suite, current->name);
            } 
            else if (sign == SIGABRT) {
                hcError("Test %s:%s aborted (Standard assert failed or abort() called)\n", current->suite, current->name);
            } 
            else if (sign == SIGFPE) {
                hcError("Floating point exception (Division by zero) in %s:%s\n", current->suite, current->name);
            } 
            else {
                hcError("Test %s:%s killed by signal %d\n", current->suite, current->name, sign);
            }
            ++results[3];
        }  else if (WIFEXITED(wstatus)) {
            int sign = WEXITSTATUS(wstatus);
            if (sign == 0) {
                hcGood("Test %s:%s runned successfully. Took %zu ms.\n", current->suite, current->name, hc_monotonic() - now);
                ++results[1];
            } else {
                ++results[2];
            }
        }
    }
}
