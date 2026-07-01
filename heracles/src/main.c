#include "heracles/heracles.h"
#include "stdio.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

typedef uint64_t timestamp;

static inline timestamp monotonic(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        return 0;
    }
    return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

static void __hc_run_test(
    struct __hc_funcStruct *current,
    unsigned long *results
)
{
    int pid = fork();
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
            ++results[2];
        }  else if (WIFEXITED(wstatus)) {
            int sign = WEXITSTATUS(wstatus);
            if (sign == 0) {
                hcGood("Test %s:%s runned successfully\n", current->suite, current->name);
                ++results[1];
            } else {
                ++results[2];
            }
        }
    }
}

int main(void)
{
    struct __hc_funcStruct *current = &__start___hc_funcStruct;
    struct __hc_funcStruct *end = &__stop___hc_funcStruct;
    char *csuite = NULL;
    unsigned long results[3] = {0, 0, 0};
    timestamp start = monotonic();

    while (current < end) {
        if (!csuite || strncmp(current->suite, csuite, 32)) {
            if (csuite) {
                printf("\n\n");
            }
            printf("========= %.32s =========\n\n", current->suite);
        }
        csuite = current->suite;
        hcInfo("Running test n°%.2zu: %s:%s\n", results[0], current->suite, current->name);
        __hc_run_test(current, results);
        printf("\n");
        ++results[0];
        ++current;
    }
    printf("========= REPORT =========\n\n");
    printf("Test runs successfully : %zu / %zu\n", results[1], results[0]);
    printf("Took %zu ms\n", monotonic() - start);
    return 0;
}
