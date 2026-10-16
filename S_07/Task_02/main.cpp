#include "robot.h"

#include <iostream>

int main()
{
    std::cout << "класс: " << QuadrupedRobot::getClassName()
              << " | объектов до создания: " << QuadrupedRobot::getObjectCount() << '\n';
    {
        std::cout << "\n=== создание объектов ===\n";
        QuadrupedRobot first;
        QuadrupedRobot second("  Арчи  ", 85, "идти вперёд", 12.5);
        for (std::size_t day = 0; day < second.getHistorySize(); ++day) {
            second.setDistanceForDay(day, 10.0 + day);
        }
        first.print();
        second.print();

        std::cout << "\n=== копирование при создании нового объекта ===\n";
        QuadrupedRobot copy = second;
        copy.print();

        std::cout << "\n=== присваивание существующему объекту ===\n";
        first = second;
        first.print();

        std::cout << "\n=== независимость копии и нормализация ===\n";
        second.setDistanceForDay(0, 999.0);
        copy.setName(" ");
        copy.setBattery(140);
        copy.setDistanceToday(-5.0);
        copy.print();

        std::cout << "\n=== константный объект ===\n";
        const QuadrupedRobot fixed(copy);
        fixed.print();
        std::cout << "заряд константного робота: " << fixed.getBattery() << '\n';
        std::cout << "\n=== выход из области видимости ===\n";
    }
    std::cout << "объектов после удаления: " << QuadrupedRobot::getObjectCount() << '\n';
    return 0;
}
