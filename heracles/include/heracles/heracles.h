/*
** FREE PROJECT, 2026
** TESTYCROUSTY
** File description:
** Single-Header test framework
*/
#ifndef __HERACLES_H
    #define __HERACLES_H
    #include <assert.h>
    #include <stddef.h>
    #include <stdio.h>

    #define hcRed "\033[31m"
    #define hcGreen "\033[32m"
    #define hcYellow "\033[33m"
    #define hcNormal "\033[0m"

    #define hcError(msg) printf(hcRed"ERROR"hcNormal": %s (%s:%d)\n", msg, __FILE__, __LINE__)

    #define Assert(condition, msg) \
    do { \
        if (!(condition)) { \
            hcError("Failed :("); \
            return; \
        } \
    } while(0)

    #define AssertEq(a, b, msg) Assert(a == b, msg)
    #define AssertNe(a, b, msg) Assert(a != b, msg)
    #define AssertLe(a, b, msg) Assert(a <= b, msg)
    #define AssertGe(a, b, msg) Assert(a >= b, msg)
    #define AssertExists(ptr, msg) Assert(ptr != NULL, msg)

    typedef void (*__hc_testFunc)(void);

    struct __hc_funcStruct {
        char suite[32];
        char name[32];
        __hc_testFunc func;
    };

    #define Test(suite, name) \
        void suite##_##name##_impl(void); \
        __attribute__((section("__hc_funcStruct"), aligned(8))) \
        static const struct __hc_funcStruct suite##_##name##_meta = { \
            #suite, #name, &suite##_##name##_impl \
        }; \
        void suite##_##name##_impl(void)

    extern struct __hc_funcStruct __start___hc_funcStruct;
    extern struct __hc_funcStruct __stop___hc_funcStruct;

#endif /* __HERACLES_H */
