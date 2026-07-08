#include "private.h"
#include <time.h>

inline timestamp kl_monotonic(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        return 0;
    }
    return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
