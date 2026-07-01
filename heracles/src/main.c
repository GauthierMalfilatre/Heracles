#include "heracles/heracles.h"
#include "stdio.h"

int main(void)
{
    struct __hc_funcStruct *current = &__start___hc_funcStruct;
    struct __hc_funcStruct *end = &__stop___hc_funcStruct;

    while (current < end) {
        printf("! Running test %s:%s\n", current->suite, current->name);
        current->func();
        ++current;
    }
    return 0;
}
