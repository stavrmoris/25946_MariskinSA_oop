#include "average.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(AssertionDemo, DISABLED_ExpectContinues)
{
    EXPECT_EQ((original::average(2, 6)), 999);
    std::cout << "после EXPECT выполнение продолжается\n";
    EXPECT_EQ((original::average(2, 6)), 998);
}

TEST(AssertionDemo, DISABLED_AssertStops)
{
    ASSERT_EQ((original::average(2, 6)), 999);
    std::cout << "после ASSERT эта строка не выполняется\n";
    EXPECT_EQ((original::average(2, 6)), 998);
}
