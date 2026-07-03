#ifndef __HC_PRIVATE_H
    #define __HC_PRIVATE_H
    #include <stdint.h>
    #include "heracles/heracles.h"
    #define HC_TOTAL 0
    #define HC_GOOD 1
    #define HC_FAILED 2
    #define HC_CRASHED 3 

typedef uint64_t timestamp;

timestamp hc_monotonic(void);

void run_test(struct __hc_funcStruct *current, unsigned long *results);

#endif /* __HC_PRIVATE_H */
