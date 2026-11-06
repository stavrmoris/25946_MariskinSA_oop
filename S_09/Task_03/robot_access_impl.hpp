#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>

template <typename Charge, typename Distance>
void setManufacturer(QuadrupedRobot<Charge, Distance>& robot, const std::string& manufacturer)
{
    std::string value = robot_detail::trimmedText(manufacturer);
    if (value.empty()) {
        throw std::invalid_argument("производитель не должен быть пустым");
    }
    robot.manufacturer_.swap(value);
}

template <typename Charge, typename Distance>
void RobotFactory::configure(QuadrupedRobot<Charge, Distance>& robot,
                             const std::string& model, const std::string& name,
                             Charge battery, const std::string& command,
                             Distance distance, const Distance (&history)[10]) const
{
    std::string new_name(name);
    std::string new_command(command);
    std::string new_model = robot_detail::trimmedText(model);
    std::string manufacturer(name_);
    QuadrupedRobot<Charge, Distance>::normalize(new_name, battery, new_command, distance);
    if (new_model.empty()) {
        throw std::invalid_argument("модель не должна быть пустой");
    }
    for (std::size_t day = 0; day < robot.history_days_; ++day) {
        if (!std::isfinite(history[day]) || history[day] < 0) {
            throw std::invalid_argument("история дистанций должна быть неотрицательной и конечной");
        }
    }
    Distance* new_history = new Distance[robot.history_days_];
    for (std::size_t day = 0; day < robot.history_days_; ++day) {
        new_history[day] = history[day];
    }
    // id не меняется, новые данные устанавливаются только после полной проверки
    robot.name_.swap(new_name);
    robot.command_.swap(new_command);
    robot.model_.swap(new_model);
    robot.manufacturer_.swap(manufacturer);
    robot.battery_ = battery;
    robot.distance_today_ = distance;
    delete[] robot.distance_history_;
    robot.distance_history_ = new_history;
}

template <typename Charge, typename Distance>
void RobotAdministrator::setModel(QuadrupedRobot<Charge, Distance>& robot,
                                   const std::string& model) const
{
    std::string value = robot_detail::trimmedText(model);
    if (value.empty()) {
        throw std::invalid_argument("модель не должна быть пустой");
    }
    robot.model_.swap(value);
}

template <typename Charge, typename Distance>
void RobotAdministrator::showModel(const QuadrupedRobot<Charge, Distance>& robot) const
{
    std::cout << "модель: " << robot.getModel() << '\n';
}
