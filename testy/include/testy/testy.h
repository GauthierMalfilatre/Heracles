/*
** FREE PROJECT, 2026
** TESTYCROUSTY
** File description:
** Single-Header test framework
*/
#ifndef __TESTY_CROUSTY_H
    #define __TESTY_CROUSTY_H
    #include <assert.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define Assert(cond, msg) static_assert(cond, msg);
    #define AssertEq(a, b, msg) Assert(a == b, msg)
    #define AssertNe(a, b, msg) Assert(a != b, msg)
    #define AssertLe(a, b, msg) Assert(a <= b, msg)
    #define AssertGe(a, b, msg) Assert(a >= b, msg)
    #define AssertExists(ptr, msg) Assert(ptr != NULL, msg)

    typedef void (*__tc_testFunc)(void);

    // struct __tc_funcHeader {
    //     size_t _capacity;
    //     size_t _usage;
    //     size_t _type_size;
    // };

    // static void *__tc_getFuncs(void)
    // {
    //     static struct __tc_funcHeader *ptr = NULL;

    //     if (!ptr) {
    //         ptr = (struct __tc_funcHeader *)malloc(sizeof(struct __tc_funcHeader));
    //         if (!ptr)
    //             return NULL;
    //         ptr->_capacity = 0;
    //         ptr->_usage = 0;
    //         ptr->_type_size = sizeof(__tc_testFunc);
    //     }
    //     return ptr + 1;
    // }

    // static int __tc_funcsPush(__tc_testFunc func)
    // {
    //     void *array = __tc_getFuncs();
    //     if (!array) {
    //         return -1;
    //     }
    //     struct __tc_funcHeader *h = ((struct __tc_funcHeader *)array) - 1;
    //     if (!h) {
    //         return -1;
    //     }
    //     if (h->_capacity >= h->_usage) {
    //         struct __tc_funcHeader *p = (struct __tc_funcHeader *)realloc(h, sizeof(struct __tc_funcHeader) + h->_type_size * h->_capacity * 2);
    //         if (p) {
    //             return -1;
    //         }
    //         h = p;
    //         h->_capacity *= 2;
    //     }
    //     array = (void *)(h + 1);
    //     *((__tc_testFunc *)array) = func;
    //     ++h->_usage;
    //     return 0;
    // }

    struct __tc_funcStruct {
        char suite[32];
        char name[32];
        __tc_testFunc func;
    };

    #define Testy(suite, name) \
        void suite##_##name##_impl(void); \
        __attribute__((section("__tc_funcStruct"), aligned(8))) \
        static const struct __tc_funcStruct suite##_##name##_meta = { \
            #suite, #name, &suite##_##name##_impl \
        }; \
        void suite##_##name##_impl(void)

    extern struct __tc_funcStruct __start___tc_funcStruct;
    extern struct __tc_funcStruct __stop___tc_funcStruct;

#endif /* __TESTY_CROUSTY_H */
