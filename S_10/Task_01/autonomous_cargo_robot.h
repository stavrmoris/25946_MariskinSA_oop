#pragma once

#include "cargo_robot.h"
#include <string>

class AutonomousCargoRobot final : private CargoRobot {
public:
    AutonomousCargoRobot();
    AutonomousCargoRobot(const std::string& name, int battery, const std::string& command,
                         double distance, double cargo_weight);
    ~AutonomousCargoRobot() override;

    using CargoRobot::show_weight;
    void showMode() const;
};
