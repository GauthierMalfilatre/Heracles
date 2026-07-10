#ifndef __kl_PRIVATE_H
    #define __kl_PRIVATE_H
    #include <stdint.h>
    #include "kronklab/kronklab.h"
    #define kl_TOTAL 0
    #define kl_GOOD 1
    #define kl_FAILED 2
    #define kl_CRASHED 3 

typedef uint64_t timestamp;

timestamp kl_monotonic(void);
timestamp kl_high_monotonic(void);

void run_test(struct __kl_funcStruct *current, unsigned long *results);
void run_bench(struct __kl_funcStruct *current, unsigned long *results);

#endif /* __kl_PRIVATE_H */
