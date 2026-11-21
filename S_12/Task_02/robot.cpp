#include "robot.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Robot::Robot(const std::string& name) : name_(name)
{
    if (name_.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("имя робота не должно быть пустым");
    }
    std::cout << "Robot: создан " << name_ << '\n';
}

Robot::~Robot() { std::cout << "Robot: уничтожен " << name_ << '\n'; }
const std::string& Robot::getName() const { return name_; }
const char* Robot::getType() const noexcept { return "Robot"; }

QuadrupedRobot::QuadrupedRobot(const std::string& name) : Robot(name)
{
    std::cout << "QuadrupedRobot: конструктор\n";
}

QuadrupedRobot::~QuadrupedRobot() { std::cout << "QuadrupedRobot: деструктор\n"; }

void QuadrupedRobot::move()
{
    std::cout << getName() << ": шагает на четырёх ногах\n";
}

const char* QuadrupedRobot::getType() const noexcept { return "QuadrupedRobot"; }

CargoRobot::CargoRobot(const std::string& name, double cargo_weight)
    : QuadrupedRobot(name), cargo_weight_(cargo_weight)
{
    if (!std::isfinite(cargo_weight_) || cargo_weight_ < 0.0) {
        throw std::invalid_argument("масса груза должна быть конечной и неотрицательной");
    }
    std::cout << "CargoRobot: конструктор\n";
}

CargoRobot::~CargoRobot() { std::cout << "CargoRobot: деструктор\n"; }

void CargoRobot::move()
{
    std::cout << getName() << ": перевозит " << cargo_weight_ << " кг на четырёх ногах\n";
}

double CargoRobot::getCargoWeight() const { return cargo_weight_; }
const char* CargoRobot::getType() const noexcept { return "CargoRobot"; }

AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, double cargo_weight,
                                           double autonomous_range)
    : CargoRobot(name, cargo_weight), autonomous_range_(autonomous_range)
{
    if (!std::isfinite(autonomous_range_) || autonomous_range_ < 0.0) {
        throw std::invalid_argument("запас хода должен быть конечным и неотрицательным");
    }
    std::cout << "AutonomousCargoRobot: конструктор\n";
}

AutonomousCargoRobot::~AutonomousCargoRobot()
{
    std::cout << "AutonomousCargoRobot: деструктор\n";
}

void AutonomousCargoRobot::move()
{
    std::cout << getName() << (autonomous_range_ > 0.0
        ? ": автономно перевозит " : ": под управлением оператора перевозит ")
        << getCargoWeight() << " кг | запас хода: " << autonomous_range_ << " км\n";
}

double AutonomousCargoRobot::getAutonomousRange() const { return autonomous_range_; }
const char* AutonomousCargoRobot::getType() const noexcept { return "AutonomousCargoRobot"; }
