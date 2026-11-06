#include "robot_squad.h"

#include <iostream>

OwnedRobotSquad::OwnedRobotSquad(const RobotFactory& factory)
{
    const double history[10]{};
    for (std::size_t i = 0; i < robots_.size(); ++i) {
        factory.configure(robots_[i], "Q-9", "Боец-" + std::to_string(i + 1),
                          100, "ожидание", 0.0, history);
    }
}

Robot& OwnedRobotSquad::getRobot(std::size_t index) { return robots_.at(index); }
const Robot& OwnedRobotSquad::getRobot(std::size_t index) const { return robots_.at(index); }
std::size_t OwnedRobotSquad::size() const { return robots_.size(); }

void OwnedRobotSquad::show() const
{
    for (const Robot& robot : robots_) {
        std::cout << robot << '\n';
    }
}

AggregatedRobotSquad::AggregatedRobotSquad(
    const std::array<std::reference_wrapper<Robot>, 5>& robots) : robots_(robots)
{
}

Robot& AggregatedRobotSquad::getRobot(std::size_t index) { return robots_.at(index).get(); }
const Robot& AggregatedRobotSquad::getRobot(std::size_t index) const { return robots_.at(index).get(); }
std::size_t AggregatedRobotSquad::size() const { return robots_.size(); }

void AggregatedRobotSquad::show() const
{
    for (const std::reference_wrapper<Robot>& reference : robots_) {
        std::cout << reference.get() << '\n';
    }
}
