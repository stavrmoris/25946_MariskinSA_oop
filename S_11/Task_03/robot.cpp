#include "robot.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace ordinary {
QuadrupedRobot::QuadrupedRobot(const std::string& name) : name_(name)
{
    if (name_.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("имя робота не должно быть пустым");
    }
    std::cout << "ordinary::QuadrupedRobot: создан " << name_ << '\n';
}

QuadrupedRobot::~QuadrupedRobot()
{
    std::cout << "ordinary::QuadrupedRobot: уничтожен " << name_ << '\n';
}

const std::string& QuadrupedRobot::getName() const { return name_; }

CargoRobot::CargoRobot(const std::string& name, double cargo_weight)
    : QuadrupedRobot(name), cargo_weight_(cargo_weight)
{
    if (!std::isfinite(cargo_weight_) || cargo_weight_ < 0.0) {
        throw std::invalid_argument("масса груза должна быть конечной и неотрицательной");
    }
    std::cout << "ordinary::CargoRobot: груз " << cargo_weight_ << " кг\n";
}

CargoRobot::~CargoRobot() { std::cout << "ordinary::CargoRobot: деструктор\n"; }
double CargoRobot::getCargoWeight() const { return cargo_weight_; }

AutonomousRobot::AutonomousRobot(const std::string& name, double autonomous_range)
    : QuadrupedRobot(name), autonomous_range_(autonomous_range)
{
    if (!std::isfinite(autonomous_range_) || autonomous_range_ < 0.0) {
        throw std::invalid_argument("запас хода должен быть конечным и неотрицательным");
    }
    std::cout << "ordinary::AutonomousRobot: запас хода " << autonomous_range_ << " км\n";
}

AutonomousRobot::~AutonomousRobot() { std::cout << "ordinary::AutonomousRobot: деструктор\n"; }
double AutonomousRobot::getAutonomousRange() const { return autonomous_range_; }

AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, double cargo_weight,
                                           double autonomous_range)
    : CargoRobot(name + " / грузовая ветвь", cargo_weight),
      AutonomousRobot(name + " / автономная ветвь", autonomous_range)
{
    std::cout << "ordinary::AutonomousCargoRobot: конструктор\n";
}

AutonomousCargoRobot::~AutonomousCargoRobot()
{
    std::cout << "ordinary::AutonomousCargoRobot: деструктор\n";
}
}

namespace fixed {
QuadrupedRobot::QuadrupedRobot(const std::string& name) : name_(name)
{
    if (name_.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("имя робота не должно быть пустым");
    }
    std::cout << "fixed::QuadrupedRobot: создан " << name_ << '\n';
}

QuadrupedRobot::~QuadrupedRobot()
{
    std::cout << "fixed::QuadrupedRobot: уничтожен " << name_ << '\n';
}

const std::string& QuadrupedRobot::getName() const { return name_; }

CargoRobot::CargoRobot(const std::string& name, double cargo_weight)
    : QuadrupedRobot(name), cargo_weight_(cargo_weight)
{
    if (!std::isfinite(cargo_weight_) || cargo_weight_ < 0.0) {
        throw std::invalid_argument("масса груза должна быть конечной и неотрицательной");
    }
    std::cout << "fixed::CargoRobot: груз " << cargo_weight_ << " кг\n";
}

CargoRobot::~CargoRobot() { std::cout << "fixed::CargoRobot: деструктор\n"; }
double CargoRobot::getCargoWeight() const { return cargo_weight_; }

AutonomousRobot::AutonomousRobot(const std::string& name, double autonomous_range)
    : QuadrupedRobot(name), autonomous_range_(autonomous_range)
{
    if (!std::isfinite(autonomous_range_) || autonomous_range_ < 0.0) {
        throw std::invalid_argument("запас хода должен быть конечным и неотрицательным");
    }
    std::cout << "fixed::AutonomousRobot: запас хода " << autonomous_range_ << " км\n";
}

AutonomousRobot::~AutonomousRobot() { std::cout << "fixed::AutonomousRobot: деструктор\n"; }
double AutonomousRobot::getAutonomousRange() const { return autonomous_range_; }

AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, double cargo_weight,
                                           double autonomous_range)
    : QuadrupedRobot(name), CargoRobot(name, cargo_weight), AutonomousRobot(name, autonomous_range)
{
    std::cout << "fixed::AutonomousCargoRobot: конструктор\n";
}

AutonomousCargoRobot::~AutonomousCargoRobot()
{
    std::cout << "fixed::AutonomousCargoRobot: деструктор\n";
}
}
