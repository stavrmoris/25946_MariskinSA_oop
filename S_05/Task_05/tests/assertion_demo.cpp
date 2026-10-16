#include "average.h"
#include <gtest/gtest.h>
#include <iostream>

// демонстрационные провалы запускаются явно через --gtest_also_run_disabled_tests
TEST(AssertionDemo, DISABLED_ExpectContinues)
{
    EXPECT_EQ((original::average<int>(2, 6)), 999);
    std::cout << "после EXPECT выполнение продолжается\n";
    EXPECT_EQ((original::average<int>(2, 6)), 998);
}

TEST(AssertionDemo, DISABLED_AssertStops)
{
    ASSERT_EQ((original::average<int>(2, 6)), 999);
    std::cout << "после ASSERT эта строка не выполняется\n";
    EXPECT_EQ((original::average<int>(2, 6)), 998);
}
