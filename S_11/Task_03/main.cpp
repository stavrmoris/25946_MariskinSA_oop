#include "robot.h"

#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    {
        std::cout << "=== алмазная проблема: два разных базовых объекта ===\n";
        ordinary::AutonomousCargoRobot robot("Арчи", 45.0, 120.0);
        ordinary::CargoRobot& cargo = robot;
        ordinary::AutonomousRobot& autonomous = robot;
        const ordinary::QuadrupedRobot* cargo_base = &cargo;
        const ordinary::QuadrupedRobot* autonomous_base = &autonomous;
        std::cout << "общая базовая часть: " << (cargo_base == autonomous_base) << '\n';
        std::cout << "имя через грузовую ветвь: " << cargo.getName() << '\n';
        std::cout << "имя через автономную ветвь: " << autonomous.getName() << '\n';
        std::cout << "груз: " << robot.getCargoWeight()
                  << " | запас хода: " << robot.getAutonomousRange() << '\n';
        // robot.getName(); // неоднозначно, есть две копии QuadrupedRobot
    }
    {
        std::cout << "\n=== решение: виртуальная база создаётся один раз ===\n";
        fixed::AutonomousCargoRobot robot("Арчи", 45.0, 120.0);
        fixed::CargoRobot& cargo = robot;
        fixed::AutonomousRobot& autonomous = robot;
        const fixed::QuadrupedRobot* cargo_base = &cargo;
        const fixed::QuadrupedRobot* autonomous_base = &autonomous;
        std::cout << "общая базовая часть: " << (cargo_base == autonomous_base) << '\n';
        std::cout << "имя без указания ветви: " << robot.getName() << '\n';
        std::cout << "груз: " << robot.getCargoWeight()
                  << " | запас хода: " << robot.getAutonomousRange() << '\n';
    }
    {
        std::cout << "\n=== представители остальных классов ===\n";
        fixed::QuadrupedRobot base("Базовый");
        fixed::CargoRobot cargo("Грузовой", 30.0);
        fixed::AutonomousRobot autonomous("Автономный", 80.0);
        std::cout << base.getName() << '\n';
        std::cout << cargo.getName() << " | груз: " << cargo.getCargoWeight() << '\n';
        std::cout << autonomous.getName() << " | запас хода: " << autonomous.getAutonomousRange() << '\n';
    }
    return 0;
}
