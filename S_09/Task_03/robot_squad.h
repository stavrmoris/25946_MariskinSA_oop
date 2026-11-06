#pragma once

#include "robot.h"

#include <array>
#include <cstddef>
#include <functional>
#include <string>

using Robot = QuadrupedRobot<int, double>;

class OwnedRobotSquad {
private:
    std::array<Robot, 5> robots_;

public:
    explicit OwnedRobotSquad(const RobotFactory& factory);
    Robot& getRobot(std::size_t index);
    const Robot& getRobot(std::size_t index) const;
    std::size_t size() const;
    void show() const;
};

class AggregatedRobotSquad {
private:
    std::array<std::reference_wrapper<Robot>, 5> robots_;

public:
    explicit AggregatedRobotSquad(const std::array<std::reference_wrapper<Robot>, 5>& robots);
    Robot& getRobot(std::size_t index);
    const Robot& getRobot(std::size_t index) const;
    std::size_t size() const;
    void show() const;
};
