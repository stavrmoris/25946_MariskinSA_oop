#include "average.h"
#include <gtest/gtest.h>
#include <limits>

TEST(OriginalAverage, PositiveNumbers)
{
    EXPECT_EQ(original::average(2, 6), 4);
}

TEST(OriginalAverage, FractionTruncatesTowardZero)
{
    EXPECT_EQ(original::average(2, 3), 2);
    EXPECT_EQ(original::average(-2, -3), -2);
}

TEST(OriginalAverage, DifferentSignsAndZero)
{
    EXPECT_EQ(original::average(-10, 4), -3);
    EXPECT_EQ(original::average(-5, 5), 0);
    EXPECT_EQ(original::average(0, 0), 0);
}

TEST(OriginalAverage, IntLimits)
{
    const int maximum = std::numeric_limits<int>::max();
    const int minimum = std::numeric_limits<int>::min();
    EXPECT_EQ(original::average(maximum, maximum), maximum);
    EXPECT_EQ(original::average(minimum, minimum), minimum);
}

TEST(ModifiedAverage, ResultHasAllowedAddition)
{
    for (int i = 0; i < 200; ++i) {
        const int result = modified::average(2, 6);
        EXPECT_GE(result, 4);
        EXPECT_LE(result, 104);
    }
}

TEST(ModifiedAverage, NegativeFractionBeforeAddition)
{
    for (int i = 0; i < 200; ++i) {
        const int result = modified::average(-2, -3);
        EXPECT_TRUE(result == -2 || (result >= -1 && result <= 97));
    }
}
