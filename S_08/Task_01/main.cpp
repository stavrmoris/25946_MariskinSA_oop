#include "robot.h"

#include <iostream>
#include <utility>

using Robot = QuadrupedRobot<int, double>;

void showReference(const Robot& robot)
{
    std::cout << "lvalue: " << robot << '\n';
}

void showReference(Robot&& robot)
{
    std::cout << "rvalue: " << robot << '\n';
}

int main()
{
    std::cout << "=== lvalue и rvalue ===\n";
    int number = 4;
    int&& reference = std::move(number);
    std::cout << "number: " << number << " | ссылка: " << reference << '\n';
    {
        Robot source("Арчи", 80, "вперёд", 12.5);
        source.setDistanceForDay(0, 100.0);
        showReference(source);
        showReference(std::move(source));
        std::cout << "после одного std::move данные не изменились: " << source << '\n';

        std::cout << "\n=== конструктор копирования ===\n";
        Robot copy(source);
        copy.setDistanceForDay(0, 200.0);
        std::cout << "источник: " << source << '\n';
        std::cout << "копия: " << copy << '\n';

        std::cout << "\n=== конструктор перемещения ===\n";
        Robot moved(std::move(source));
        std::cout << "получатель: " << moved << '\n';
        std::cout << "источник после перемещения: " << source << '\n';
        source.setDistanceForDay(0, 50.0);
        std::cout << "источник снова используется: " << source << '\n';

        std::cout << "\n=== копирующее присваивание ===\n";
        Robot assigned;
        assigned = copy;
        std::cout << assigned << '\n';

        std::cout << "\n=== перемещающее присваивание ===\n";
        Robot target;
        target = std::move(moved);
        std::cout << "получатель: " << target << '\n';
        std::cout << "источник: " << moved << '\n';

        std::cout << "\n=== непосредственное создание из временного объекта ===\n";
        Robot direct = Robot("Рекс", 70, "стоп", 3.5);
        std::cout << "в C++17 здесь нет вызова copy или move конструктора\n" << direct << '\n';
        std::cout << "объектов перед выходом: " << Robot::getObjectCount() << '\n';
    }
    std::cout << "объектов после выхода: " << Robot::getObjectCount() << '\n';
    return 0;
}
