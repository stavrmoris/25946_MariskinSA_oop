#include "robot.h"
#include <gtest/gtest.h>

#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

TEST(Robot, DefaultConstructor)
{
    const QuadrupedRobot robot;
    EXPECT_FALSE(robot.getId().empty());
    EXPECT_EQ(robot.getName(), "робот");
    EXPECT_EQ(robot.getBattery(), 100);
    EXPECT_EQ(robot.getCommand(), "ожидание");
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 0.0);
    EXPECT_EQ(robot.getHistorySize(), 10U);
    for (std::size_t day = 0; day < robot.getHistorySize(); ++day) {
        EXPECT_DOUBLE_EQ(robot.getDistanceForDay(day), 0.0);
    }
}

TEST(Robot, InitializingConstructor)
{
    const QuadrupedRobot robot("Арчи", 75, "вперёд", 12.5);
    EXPECT_EQ(robot.getName(), "Арчи");
    EXPECT_EQ(robot.getBattery(), 75);
    EXPECT_EQ(robot.getCommand(), "вперёд");
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 12.5);
}

TEST(Robot, ConstructorNormalizesFields)
{
    const QuadrupedRobot robot(" \t", -20, " ", -4.0);
    EXPECT_EQ(robot.getName(), "робот");
    EXPECT_EQ(robot.getBattery(), 0);
    EXPECT_EQ(robot.getCommand(), "ожидание");
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 0.0);
    const QuadrupedRobot trimmed("  Арчи  ", 120, "  стоп  ", 1.0);
    EXPECT_EQ(trimmed.getName(), "Арчи");
    EXPECT_EQ(trimmed.getBattery(), 100);
    EXPECT_EQ(trimmed.getCommand(), "стоп");
}

TEST(Robot, SettersPreserveInvariant)
{
    QuadrupedRobot robot;
    robot.setName("  Рекс  ");
    robot.setBattery(60);
    robot.setCommand("  стоять  ");
    robot.setDistanceToday(5.5);
    EXPECT_EQ(robot.getName(), "Рекс");
    EXPECT_EQ(robot.getBattery(), 60);
    EXPECT_EQ(robot.getCommand(), "стоять");
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 5.5);
    robot.setName("");
    robot.setBattery(200);
    robot.setCommand("");
    robot.setDistanceToday(-1.0);
    EXPECT_EQ(robot.getName(), "робот");
    EXPECT_EQ(robot.getBattery(), 100);
    EXPECT_EQ(robot.getCommand(), "ожидание");
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 0.0);
    robot.setBattery(-1);
    EXPECT_EQ(robot.getBattery(), 0);
}

TEST(Robot, NonFiniteDistanceNormalizesToZero)
{
    QuadrupedRobot robot("Рекс", 50, "стоп", std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 0.0);
    robot.setDistanceToday(std::numeric_limits<double>::quiet_NaN());
    EXPECT_DOUBLE_EQ(robot.getDistanceToday(), 0.0);
    robot.setDistanceForDay(0, std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(robot.getDistanceForDay(0), 0.0);
}

TEST(Robot, HistoryAndBounds)
{
    QuadrupedRobot robot;
    for (std::size_t day = 0; day < robot.getHistorySize(); ++day) {
        robot.setDistanceForDay(day, 1.5 + day);
        EXPECT_DOUBLE_EQ(robot.getDistanceForDay(day), 1.5 + day);
    }
    robot.setDistanceForDay(0, -2.0);
    EXPECT_DOUBLE_EQ(robot.getDistanceForDay(0), 0.0);
    EXPECT_THROW(robot.getDistanceForDay(10), std::out_of_range);
    EXPECT_THROW(robot.setDistanceForDay(10, 5.0), std::out_of_range);
}

TEST(Robot, CopyConstructorCreatesIndependentObject)
{
    QuadrupedRobot source("Арчи", 70, "вперёд", 20.0);
    source.setDistanceForDay(0, 12.0);
    QuadrupedRobot copy(source);
    EXPECT_NE(copy.getId(), source.getId());
    EXPECT_EQ(copy.getName(), source.getName());
    EXPECT_EQ(copy.getBattery(), source.getBattery());
    EXPECT_EQ(copy.getCommand(), source.getCommand());
    EXPECT_DOUBLE_EQ(copy.getDistanceToday(), source.getDistanceToday());
    EXPECT_DOUBLE_EQ(copy.getDistanceForDay(0), 12.0);
    copy.setDistanceForDay(0, 99.0);
    copy.setName("копия");
    EXPECT_DOUBLE_EQ(source.getDistanceForDay(0), 12.0);
    EXPECT_EQ(source.getName(), "Арчи");
}

TEST(Robot, AssignmentCopiesDataAndPreservesId)
{
    QuadrupedRobot source("Арчи", 70, "вперёд", 20.0);
    source.setDistanceForDay(9, 17.0);
    QuadrupedRobot target;
    const std::string old_id = target.getId();
    QuadrupedRobot& returned = (target = source);
    EXPECT_EQ(&returned, &target);
    EXPECT_EQ(target.getId(), old_id);
    EXPECT_NE(target.getId(), source.getId());
    EXPECT_EQ(target.getName(), source.getName());
    EXPECT_EQ(target.getBattery(), source.getBattery());
    EXPECT_EQ(target.getCommand(), source.getCommand());
    EXPECT_DOUBLE_EQ(target.getDistanceToday(), source.getDistanceToday());
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(9), 17.0);
    source.setDistanceForDay(9, 1.0);
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(9), 17.0);
}

TEST(Robot, SelfAssignmentAndRepeatedAssignment)
{
    QuadrupedRobot robot("Рекс", 40, "стоп", 3.0);
    robot.setDistanceForDay(0, 8.0);
    const std::string id = robot.getId();
    QuadrupedRobot* same = &robot;
    robot = *same;
    EXPECT_EQ(robot.getId(), id);
    EXPECT_DOUBLE_EQ(robot.getDistanceForDay(0), 8.0);
    QuadrupedRobot target;
    target = robot;
    target = robot;
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 8.0);
}

TEST(Robot, CopySurvivesSourceDestruction)
{
    QuadrupedRobot target;
    {
        QuadrupedRobot source;
        source.setDistanceForDay(0, 42.0);
        target = source;
    }
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 42.0);
}

TEST(Robot, IdsAreUniqueAndReadOnly)
{
    const QuadrupedRobot first;
    const QuadrupedRobot second(first);
    const QuadrupedRobot third;
    EXPECT_NE(first.getId(), second.getId());
    EXPECT_NE(first.getId(), third.getId());
    EXPECT_NE(second.getId(), third.getId());
    EXPECT_TRUE((std::is_same<decltype(std::declval<const QuadrupedRobot&>().getId()),
                              const std::string&>::value));
}

TEST(Robot, LifecycleMessagesAndConstPrint)
{
    testing::internal::CaptureStdout();
    {
        QuadrupedRobot first;
        QuadrupedRobot second("Арчи", 50, "стоп", 1.0);
        const QuadrupedRobot copy(second);
        first = second;
        copy.print();
    }
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("конструктор по умолчанию"), std::string::npos);
    EXPECT_NE(output.find("инициализирующий конструктор"), std::string::npos);
    EXPECT_NE(output.find("конструктор копирования"), std::string::npos);
    EXPECT_NE(output.find("оператор присваивания"), std::string::npos);
    EXPECT_NE(output.find("деструктор"), std::string::npos);
    EXPECT_NE(output.find("история за последние 10 дней"), std::string::npos);
}

TEST(Robot, CountsOnlyLivingObjects)
{
    const std::size_t before = QuadrupedRobot::getObjectCount();
    {
        QuadrupedRobot first;
        EXPECT_EQ(QuadrupedRobot::getObjectCount(), before + 1);
        QuadrupedRobot second("Арчи", 50, "стоп", 1.0);
        EXPECT_EQ(QuadrupedRobot::getObjectCount(), before + 2);
        {
            const QuadrupedRobot copy(second);
            EXPECT_EQ(QuadrupedRobot::getObjectCount(), before + 3);
            first = copy;
            EXPECT_EQ(QuadrupedRobot::getObjectCount(), before + 3);
        }
        EXPECT_EQ(QuadrupedRobot::getObjectCount(), before + 2);
    }
    EXPECT_EQ(QuadrupedRobot::getObjectCount(), before);
}

TEST(Robot, ClassNameAndCountInMessages)
{
    EXPECT_EQ(QuadrupedRobot::getClassName(), "QuadrupedRobot");
    testing::internal::CaptureStdout();
    {
        QuadrupedRobot robot;
    }
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("QuadrupedRobot | robot-"), std::string::npos);
    EXPECT_NE(output.find("объектов:"), std::string::npos);
}
