/*
** FREE PROJECT, 2026
** TESTYCROUSTY
** File description:
** Single-Header test framework
*/
#ifndef __kronklab_H
    #define __kronklab_H
    #include <assert.h>
    #include <stddef.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define klRed "\033[31m"
    #define klGreen "\033[32m"
    #define klYellow "\033[33m"
    #define klNormal "\033[0m"

    #define klError(msg, ...) printf(klRed "ERROR" klNormal ": " msg, ##__VA_ARGS__)
    #define klInfo(msg, ...) printf(klYellow "INFO" klNormal ": " msg, ##__VA_ARGS__)
    #define klGood(msg, ...) printf(klGreen "GOOD" klNormal ": " msg, ##__VA_ARGS__)

    #define Assert(condition, msg, ...) \
    do { \
        if (!(condition)) { \
            klError("Failed at %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
            exit(1); \
        } \
    } while(0)

    #define AssertEq(a, b, msg, ...) Assert(a == b, msg, ##__VA_ARGS__)
    #define AssertNe(a, b, msg, ...) Assert(a != b, msg, ##__VA_ARGS__)
    #define AssertLe(a, b, msg, ...) Assert(a <= b, msg, ##__VA_ARGS__)
    #define AssertGe(a, b, msg, ...) Assert(a >= b, msg, ##__VA_ARGS__)
    #define AssertNull(ptr, msg, ...) Assert(ptr == NULL, msg, ##__VA_ARGS__)
    #define AssertNotNull(ptr, msg, ...) Assert(ptr != NULL, msg, ##__VA_ARGS__)
    #define AssertStrEq(str1, str2, msg, ...) AssertEq(strcmp(str1, str2), 0, msg, ##__VA_ARGS__)
    #define AssertStrNe(str1, str2, msg, ...) AssertNe(strcmp(str1, str2), 0, msg, ##__VA_ARGS__)

    typedef void (*__kl_testFunc)(void);

    struct __kl_funcStruct {
        char suite[32];
        char name[32];
        __kl_testFunc func;
    };

    #define Test(suite, name) \
        void suite##_##name##_impl(void); \
        __attribute__((section("__kl_funcStruct"), aligned(8), used, retain)) \
        static const struct __kl_funcStruct suite##_##name##_meta = { \
            #suite, #name, &suite##_##name##_impl \
        }; \
        void suite##_##name##_impl(void)

    extern struct __kl_funcStruct __start___kl_funcStruct;
    extern struct __kl_funcStruct __stop___kl_funcStruct;

#endif /* __kronklab_H */
