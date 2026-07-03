#include "heracles/heracles.h"
#include "private.h"
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    struct __hc_funcStruct *current = &__start___hc_funcStruct;
    struct __hc_funcStruct *end = &__stop___hc_funcStruct;
    char *csuite = NULL;
    unsigned long results[4] = {0, 0, 0};
    timestamp start = hc_monotonic();

    while (current < end) {
        if (!csuite || strncmp(current->suite, csuite, 32)) {
            if (csuite) {
                printf("\n");
            }
            printf("========= %.32s =========\n\n", current->suite);
        }
        csuite = current->suite;
        hcInfo("Running test n°%.2zu: %s:%s\n", results[0], current->suite, current->name);
        run_test(current, results);
        printf("\n");
        ++results[0];
        ++current;
    }
    printf("\n========= REPORT =========\n\n");
    printf("[REPORT] total [%zu] | passed ["hcGreen"%zu"hcNormal"] | failed ["hcRed"%zu"hcNormal"] | crashed ["hcRed"%zu"hcNormal"]\n", results[HC_TOTAL], results[HC_GOOD], results[HC_FAILED], results[HC_CRASHED]);
    printf("[REPORT] Took [%zu] milliseconds\n", hc_monotonic() - start);
    return 0;
}
