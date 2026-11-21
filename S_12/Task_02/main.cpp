#include "robot.h"

#include <array>
#include <iostream>
#include <memory>

int main()
{
    QuadrupedRobot quadruped("Арчи");
    CargoRobot cargo("Грузовой", 45.0);
    AutonomousCargoRobot autonomous("Автономный", 30.0, 120.0);
    std::array<Robot*, 3> robots{&quadruped, &cargo, &autonomous};

    std::cout << "\n=== прямые вызовы невиртуального метода ===\n";
    std::cout << quadruped.getType() << '\n' << cargo.getType() << '\n'
              << autonomous.getType() << '\n';

    std::cout << "\n=== неполиморфное поведение через Robot* ===\n";
    for (const Robot* robot : robots) {
        std::cout << robot->getName() << " | тип: " << robot->getType() << '\n';
    }

    std::cout << "\n=== полиморфное поведение move() через те же Robot* ===\n";
    for (Robot* robot : robots) {
        robot->move();
    }

    std::cout << "\n=== явный выбор реализации подавляет виртуальный вызов ===\n";
    const std::array<QuadrupedRobot*, 3> quadrupeds{&quadruped, &cargo, &autonomous};
    for (QuadrupedRobot* robot : quadrupeds) {
        robot->QuadrupedRobot::move();
    }

    std::cout << "\n=== виртуальный деструктор через базовый указатель ===\n";
    {
        std::unique_ptr<Robot> owned = std::make_unique<AutonomousCargoRobot>(
            "Без автономного запаса", 10.0, 0.0);
        owned->move();
    }
    // Robot robot("Базовый"); // абстрактный класс нельзя создать
    return 0;
}
