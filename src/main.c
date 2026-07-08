#include "kronklab/kronklab.h"
#include "private.h"
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    struct __kl_funcStruct *current = &__start___kl_funcStruct;
    struct __kl_funcStruct *end = &__stop___kl_funcStruct;
    char *csuite = NULL;
    unsigned long results[4] = {0, 0, 0};
    timestamp start = kl_monotonic();

    while (current < end) {
        if (!csuite || strncmp(current->suite, csuite, 32)) {
            if (csuite) {
                printf("\n");
            }
            printf("========= %.32s =========\n\n", current->suite);
        }
        csuite = current->suite;
        klInfo("Running test n°%.2zu: %s:%s\n", results[0], current->suite, current->name);
        run_test(current, results);
        printf("\n");
        ++results[0];
        ++current;
    }
    printf("\n========= REPORT =========\n\n");
    printf("[REPORT] total [%zu] | passed ["klGreen"%zu"klNormal"] | failed ["klRed"%zu"klNormal"] | crashed ["klRed"%zu"klNormal"]\n", results[kl_TOTAL], results[kl_GOOD], results[kl_FAILED], results[kl_CRASHED]);
    printf("[REPORT] Took [%zu] milliseconds\n", kl_monotonic() - start);
    return 0;
}
