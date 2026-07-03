#include "heracles/heracles.h"
#include <stdio.h>
#include <unistd.h>

Test(test1, test_assert_eq)
{
    AssertEq(1, 1, "1 is not equal to 1");
}

Test(test1, test_assert_ne)
{
    AssertNe(1, 1, "1 is equal to 1");
}

Test(test_segv, segv)
{
    int * a = 0;
    *a = 0;

    AssertEq(1, 1, "1 and 1 should be equal...");
}

Test(test_segv, segv2)
{
    AssertNull(NULL, "Wait ??");
}
