#include "autonomous_cargo_robot.h"

#include <iostream>
#include <random>

AutonomousCargoRobot::AutonomousCargoRobot() : CargoRobot()
{
    std::cout << "[автономный | " << getId() << "] конструктор по умолчанию\n";
}

AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, int battery,
                                           const std::string& command, double distance,
                                           double cargo_weight)
    : CargoRobot(name, battery, command, distance, cargo_weight)
{
    std::cout << "[автономный | " << getId() << "] инициализирующий конструктор\n";
}

AutonomousCargoRobot::~AutonomousCargoRobot()
{
    std::cout << "[автономный | " << getId() << "] деструктор\n";
}

void AutonomousCargoRobot::showMode() const
{
    static std::mt19937 generator(std::random_device{}());
    static std::bernoulli_distribution autonomous(0.5);
    std::cout << "[" << getId() << "] режим: "
              << (autonomous(generator) ? "автономный" : "управляемый") << '\n';
}
