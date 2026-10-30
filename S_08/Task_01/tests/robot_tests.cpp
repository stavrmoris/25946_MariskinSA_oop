#include "robot.h"
#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using Robot = QuadrupedRobot<int, double>;
using FloatRobot = QuadrupedRobot<long long, float>;

class RobotTest : public testing::Test {
protected:
    Robot robot_{"Арчи", 80, "вперёд", 12.5};
    FloatRobot float_robot_{"Рекс", 60LL, "стоп", 3.25f};

    void SetUp() override
    {
        robot_.setDistanceForDay(0, 100.0);
        float_robot_.setDistanceForDay(0, 100.0f);
    }
};

TEST_F(RobotTest, InitialState)
{
    EXPECT_EQ(robot_.getName(), "Арчи");
    EXPECT_EQ(robot_.getBattery(), 80);
    EXPECT_EQ(robot_.getCommand(), "вперёд");
    EXPECT_DOUBLE_EQ(robot_.getDistanceToday(), 12.5);
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 100.0);
    EXPECT_EQ(float_robot_.getBattery(), 60LL);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceToday(), 3.25f);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceForDay(0), 100.0f);
}

TEST_F(RobotTest, HistoryChangesAreLocalToFixture)
{
    robot_.setDistanceForDay(0, 999.0);
    float_robot_.setDistanceForDay(0, 999.0f);
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 999.0);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceForDay(0), 999.0f);
}

TEST_F(RobotTest, FreshFixtureStartsWithOriginalHistory)
{
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 100.0);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceForDay(0), 100.0f);
}

TEST_F(RobotTest, InvalidValuesKeepPreviousState)
{
    EXPECT_THROW(robot_.setBattery(150), std::invalid_argument);
    EXPECT_THROW(robot_.setName(" "), std::invalid_argument);
    EXPECT_THROW(robot_.setDistanceForDay(0, -1.0), std::invalid_argument);
    EXPECT_THROW(robot_.getDistanceForDay(10), std::out_of_range);
    EXPECT_EQ(robot_.getBattery(), 80);
    EXPECT_EQ(robot_.getName(), "Арчи");
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 100.0);
    EXPECT_THROW(float_robot_.setBattery(-1LL), std::invalid_argument);
    EXPECT_THROW(float_robot_.setDistanceToday(-1.0f), std::invalid_argument);
    EXPECT_EQ(float_robot_.getBattery(), 60LL);
}

TEST_F(RobotTest, CopyConstructorUsesIndependentHistory)
{
    const std::size_t before = Robot::getObjectCount();
    {
        Robot copy(robot_);
        EXPECT_EQ(Robot::getObjectCount(), before + 1);
        EXPECT_NE(copy.getId(), robot_.getId());
        EXPECT_DOUBLE_EQ(copy.getDistanceForDay(0), 100.0);
        copy.setDistanceForDay(0, 200.0);
        EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 100.0);
    }
    EXPECT_EQ(Robot::getObjectCount(), before);
}

TEST_F(RobotTest, MoveConstructorTransfersDataAndKeepsSourceUsable)
{
    const std::size_t before = Robot::getObjectCount();
    const std::string source_id = robot_.getId();
    {
        Robot moved(std::move(robot_));
        EXPECT_EQ(Robot::getObjectCount(), before + 1);
        EXPECT_NE(moved.getId(), source_id);
        EXPECT_EQ(robot_.getId(), source_id);
        EXPECT_EQ(moved.getName(), "Арчи");
        EXPECT_EQ(moved.getBattery(), 80);
        EXPECT_DOUBLE_EQ(moved.getDistanceForDay(0), 100.0);
        EXPECT_FALSE(robot_.getName().empty());
        EXPECT_FALSE(robot_.getCommand().empty());
        EXPECT_EQ(robot_.getBattery(), 0);
        EXPECT_DOUBLE_EQ(robot_.getDistanceToday(), 0.0);
        EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 0.0);
        robot_.setDistanceForDay(0, 55.0);
        EXPECT_DOUBLE_EQ(moved.getDistanceForDay(0), 100.0);
    }
    EXPECT_EQ(Robot::getObjectCount(), before);
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 55.0);
}

TEST_F(RobotTest, CopyAssignmentPreservesId)
{
    Robot target;
    const std::string id = target.getId();
    const std::size_t before = Robot::getObjectCount();
    Robot& returned = (target = robot_);
    EXPECT_EQ(&returned, &target);
    EXPECT_EQ(target.getId(), id);
    EXPECT_EQ(Robot::getObjectCount(), before);
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 100.0);
    robot_.setDistanceForDay(0, 200.0);
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 100.0);
}

TEST_F(RobotTest, MoveAssignmentPreservesIdsAndCount)
{
    Robot target("Получатель", 50, "ожидание", 1.0);
    target.setDistanceForDay(0, 999.0);
    const std::string id = target.getId();
    const std::string source_id = robot_.getId();
    const std::size_t before = Robot::getObjectCount();
    Robot& returned = (target = std::move(robot_));
    EXPECT_EQ(&returned, &target);
    EXPECT_EQ(target.getId(), id);
    EXPECT_EQ(robot_.getId(), source_id);
    EXPECT_EQ(Robot::getObjectCount(), before);
    EXPECT_EQ(target.getName(), "Арчи");
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 100.0);
    EXPECT_FALSE(robot_.getName().empty());
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 0.0);
    robot_.setDistanceForDay(0, 25.0);
    EXPECT_DOUBLE_EQ(target.getDistanceForDay(0), 100.0);
}

TEST_F(RobotTest, SelfCopyAndSelfMoveKeepData)
{
    Robot* same = &robot_;
    robot_ = *same;
    robot_ = std::move(*same);
    EXPECT_EQ(robot_.getName(), "Арчи");
    EXPECT_DOUBLE_EQ(robot_.getDistanceForDay(0), 100.0);
}

TEST_F(RobotTest, CopyAndMoveFromAlreadyMovedObject)
{
    Robot owner(std::move(robot_));
    Robot copy(robot_);
    Robot moved_again(std::move(robot_));
    EXPECT_DOUBLE_EQ(copy.getDistanceForDay(0), 0.0);
    EXPECT_DOUBLE_EQ(moved_again.getDistanceForDay(0), 0.0);
    copy = robot_;
    EXPECT_DOUBLE_EQ(copy.getDistanceForDay(0), 0.0);
    EXPECT_DOUBLE_EQ(owner.getDistanceForDay(0), 100.0);
}

TEST_F(RobotTest, FloatSpecializationSupportsCopyAndMove)
{
    FloatRobot copy(float_robot_);
    copy.setDistanceForDay(0, 25.0f);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceForDay(0), 100.0f);
    FloatRobot moved(std::move(float_robot_));
    EXPECT_FLOAT_EQ(moved.getDistanceForDay(0), 100.0f);
    EXPECT_FLOAT_EQ(float_robot_.getDistanceForDay(0), 0.0f);
    const std::string copy_id = copy.getId();
    copy = std::move(moved);
    EXPECT_EQ(copy.getId(), copy_id);
    EXPECT_FLOAT_EQ(copy.getDistanceForDay(0), 100.0f);
    EXPECT_FLOAT_EQ(moved.getDistanceForDay(0), 0.0f);
}

TEST_F(RobotTest, OutputOfMovedSourceAndInputReuse)
{
    Robot moved(std::move(robot_));
    std::ostringstream output;
    output << robot_;
    EXPECT_NE(output.str().find(robot_.getId()), std::string::npos);
    std::istringstream input("\"Новый\" 70 \"стоп\" 4.5");
    input >> robot_;
    EXPECT_FALSE(input.fail());
    EXPECT_EQ(robot_.getName(), "Новый");
    EXPECT_DOUBLE_EQ(robot_.getDistanceToday(), 4.5);
    EXPECT_DOUBLE_EQ(moved.getDistanceForDay(0), 100.0);
}

TEST_F(RobotTest, FailedConstructionDoesNotIncreaseCount)
{
    const std::size_t before = Robot::getObjectCount();
    EXPECT_THROW((Robot("Арчи", 150, "стоп", 1.0)), std::invalid_argument);
    EXPECT_EQ(Robot::getObjectCount(), before);
}

TEST_F(RobotTest, ConstRvalueUsesCopyConstructor)
{
    const Robot source(robot_);
    Robot copy(std::move(source));
    EXPECT_NE(copy.getId(), source.getId());
    copy.setDistanceForDay(0, 20.0);
    EXPECT_DOUBLE_EQ(source.getDistanceForDay(0), 100.0);
}
