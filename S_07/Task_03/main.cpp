#include "robot.h"
#include <iostream>

int main()
{
    std::cout << "=== статические значения ===\n";
    std::cout << "объектов: " << QuadrupedRobot::getObjectCount() << '\n';
    std::cout << QuadrupedRobot::getClassName() << "\n\n";

    std::cout << "=== создание первого робота ===\n";
    QuadrupedRobot first_robot("Арчи", 85, "идти вперёд", 12.5);
    first_robot.print();
    std::cout << "объектов: " << first_robot.getObjectCount() << '\n';
    std::cout << first_robot << "\n\n";

    std::cout << "=== второй робот ===\n";
    QuadrupedRobot second_robot{first_robot};
    std::cout << second_robot << '\n';
    second_robot.setDistanceForDay(0, 222.0);
    first_robot.setDistanceForDay(0, 111.0);
    second_robot.print();

    {
        std::cout << "=== внутри блока ===\n";
        QuadrupedRobot second_robot{first_robot};
        std::cout << second_robot << '\n';
        second_robot.setDistanceForDay(0, 30.0);
        first_robot.setDistanceForDay(0, 40.0);
        second_robot.print();
    }

    std::cout << "=== после блока ===\n";
    second_robot.print();
    std::cout << "объектов: " << QuadrupedRobot::getObjectCount() << '\n';
    return 0;
}
