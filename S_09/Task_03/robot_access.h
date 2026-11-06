#pragma once

#include <string>

template <typename Charge, typename Distance>
class QuadrupedRobot;

template <typename Charge, typename Distance>
void setManufacturer(QuadrupedRobot<Charge, Distance>& robot, const std::string& manufacturer);

class RobotFactory {
private:
    std::string name_;

public:
    explicit RobotFactory(const std::string& name);
    const std::string& getName() const;

    template <typename Charge, typename Distance>
    void configure(QuadrupedRobot<Charge, Distance>& robot, const std::string& model,
                   const std::string& name, Charge battery, const std::string& command,
                   Distance distance, const Distance (&history)[10]) const;
};

class RobotAdministrator {
public:
    template <typename Charge, typename Distance>
    void setModel(QuadrupedRobot<Charge, Distance>& robot, const std::string& model) const;

    template <typename Charge, typename Distance>
    void showModel(const QuadrupedRobot<Charge, Distance>& robot) const;
};
