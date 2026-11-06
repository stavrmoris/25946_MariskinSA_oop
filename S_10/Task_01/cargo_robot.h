#pragma once

#include "robot.h"
#include <string>

class CargoRobot : public QuadrupedRobot {
private:
    static constexpr double max_cargo_weight_ = 100.0;
    double cargo_weight_;

public:
    CargoRobot();
    CargoRobot(const std::string& name, int battery, const std::string& command,
               double distance, double cargo_weight);
    ~CargoRobot() override;

    void setCargoWeight(double weight);
    double getCargoWeight() const;
    static double getMaxCargoWeight();
    void show_weight() const;
};
