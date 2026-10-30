#pragma once

#include <ostream>

template <typename Charge, typename Distance>
void renameRobot(QuadrupedRobot<Charge, Distance>& robot, const std::string& name)
{
    robot.setState(name, robot.battery_, robot.command_, robot.distance_today_);
}

template <typename Charge, typename Distance>
void RobotTechnician::recharge(QuadrupedRobot<Charge, Distance>& robot, Charge battery) const
{
    robot.setState(robot.name_, battery, robot.command_, robot.distance_today_);
}

template <typename Charge, typename Distance>
void RobotTechnician::resetToday(QuadrupedRobot<Charge, Distance>& robot) const
{
    robot.distance_today_ = Distance{};
}

template <typename Charge, typename Distance>
void RobotTechnician::addServiceEntry(QuadrupedRobot<Charge, Distance>& robot,
                                      const std::string& text) const
{
    robot.maintenance_.addEntry(text);
}

template <typename Charge, typename Distance>
void RobotTechnician::connect(QuadrupedRobot<Charge, Distance>& robot, ControlStation& station) const
{
    robot.station_ = &station;
}

template <typename Charge, typename Distance>
void RobotTechnician::disconnect(QuadrupedRobot<Charge, Distance>& robot) const
{
    robot.station_ = nullptr;
}

template <typename Charge, typename Distance>
void RobotInspector::clearHistory(QuadrupedRobot<Charge, Distance>& robot) const
{
    if (robot.distance_history_) {
        for (std::size_t day = 0; day < robot.history_days_; ++day) {
            robot.distance_history_[day] = Distance{};
        }
    }
}

template <typename Charge, typename Distance>
void RobotInspector::describe(const QuadrupedRobot<Charge, Distance>& robot,
                              std::ostream& output) const
{
    // этот метод не friend и использует только публичный интерфейс
    output << "инспектор: " << robot.getId() << " | имя: " << robot.getName() << '\n';
}
