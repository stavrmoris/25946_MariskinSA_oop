#include "robot.h"
#include <iostream>
#include <limits>
#include <stdexcept>

int main()
{
    QuadrupedRobot<int, double> robot;
    for (;;) {
        std::cout << "введите имя, заряд (0-100), команду и дистанцию\n"
                  << "пример: \"Арчи\" 80 \"идти вперёд\" 12.5\n";
        try {
            if (std::cin >> robot) {
                break;
            }
            if (std::cin.eof()) {
                return 1;
            }
            std::cout << "ошибка формата, повторите ввод\n";
            std::cin.clear();
        } catch (const std::invalid_argument& error) {
            std::cout << "ошибка: " << error.what() << "; исправьте данные\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << robot << '\n';
    std::cout << "=== другая специализация: long long и float ===\n";
    QuadrupedRobot<long long, float> other("Рекс", 75LL, "стоп", 3.25f);
    std::cout << other << '\n';
    const QuadrupedRobot<int, double> copy(robot);
    std::cout << copy << '\n';
    return 0;
}
