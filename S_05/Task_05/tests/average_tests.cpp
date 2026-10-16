#include "average.h"
#include <gtest/gtest.h>
#include <limits>

TEST(OriginalAverage, PositiveNumbers)
{
    EXPECT_EQ(original::average<int>(2, 6), 4);
}

TEST(OriginalAverage, FractionTruncatesTowardZero)
{
    EXPECT_EQ(original::average<int>(2, 3), 2);
    EXPECT_EQ(original::average<int>(-2, -3), -2);
}

TEST(OriginalAverage, DifferentSignsAndZero)
{
    EXPECT_EQ(original::average<int>(-10, 4), -3);
    EXPECT_EQ(original::average<int>(-5, 5), 0);
    EXPECT_EQ(original::average<int>(0, 0), 0);
}

TEST(OriginalAverage, IntLimits)
{
    const int maximum = std::numeric_limits<int>::max();
    const int minimum = std::numeric_limits<int>::min();
    EXPECT_EQ(original::average<int>(maximum, maximum), maximum);
    EXPECT_EQ(original::average<int>(minimum, minimum), minimum);
}

TEST(ModifiedAverage, ResultHasAllowedAddition)
{
    // проверяем допустимые результаты, не требуем определённого исхода случайного выбора
    for (int i = 0; i < 200; ++i) {
        const int result = modified::average<int>(2, 6);
        EXPECT_GE(result, 4);
        EXPECT_LE(result, 104);
    }
}

TEST(ModifiedAverage, NegativeFractionBeforeAddition)
{
    for (int i = 0; i < 200; ++i) {
        const int result = modified::average<int>(-2, -3);
        // среднее -2,5 с добавкой от 1 до 100 даёт целые результаты от -1 до 97
        EXPECT_TRUE(result == -2 || (result >= -1 && result <= 97));
    }
}

TEST(TemplateAverage, DoubleResultFromIntArguments)
{
    EXPECT_DOUBLE_EQ((original::average<double, int>(2, 3)), 2.5);
}

TEST(TemplateAverage, DoubleArguments)
{
    EXPECT_DOUBLE_EQ((original::average<double, double>(1.5, 2.5)), 2.0);
    EXPECT_EQ((original::average<int, double>(1.5, 2.5)), 2);
}

TEST(TemplateAverage, ModifiedDoubleResult)
{
    for (int i = 0; i < 200; ++i) {
        const double result = modified::average<double, double>(1.5, 3.5);
        EXPECT_GE(result, 2.5);
        EXPECT_LE(result, 102.5);
        EXPECT_DOUBLE_EQ(result - static_cast<int>(result), 0.5);
    }
}
