#include "testy/testy.h"

Testy(test1, test_assert_eq)
{
    AssertEq(1, 1, "1 is not equal to 1\n");
}

Testy(test1, test_assert_ne)
{
    AssertEq(1, 1, "1 is equal to 1\n");
}
