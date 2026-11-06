#include "cargo_robot.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

CargoRobot::CargoRobot() : QuadrupedRobot(), cargo_weight_(0.0)
{
    std::cout << "[грузовой | " << getId() << "] конструктор по умолчанию\n";
}

CargoRobot::CargoRobot(const std::string& name, int battery, const std::string& command,
                       double distance, double cargo_weight)
    : QuadrupedRobot(name, battery, command, distance), cargo_weight_(0.0)
{
    setCargoWeight(cargo_weight);
    std::cout << "[грузовой | " << getId() << "] инициализирующий конструктор\n";
}

CargoRobot::~CargoRobot()
{
    std::cout << "[грузовой | " << getId() << "] деструктор\n";
}

void CargoRobot::setCargoWeight(double weight)
{
    if (!std::isfinite(weight) || weight < 0.0 || weight > max_cargo_weight_) {
        throw std::invalid_argument("масса груза должна быть от 0 до 100 кг");
    }
    cargo_weight_ = weight;
}

double CargoRobot::getCargoWeight() const { return cargo_weight_; }
double CargoRobot::getMaxCargoWeight() { return max_cargo_weight_; }

void CargoRobot::show_weight() const
{
    std::cout << "[" << getId() << "] масса груза: " << cargo_weight_
              << " кг | максимум: " << max_cargo_weight_ << " кг\n";
}
