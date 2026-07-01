#include "heracles/heracles.h"

Test(test1, test_assert_eq)
{
    AssertEq(1, 1, "1 is not equal to 1");
}

Test(test1, test_assert_ne)
{
    AssertNe(1, 1, "1 is equal to 1");
}
