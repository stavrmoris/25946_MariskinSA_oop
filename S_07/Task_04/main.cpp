#include "robot.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

int main()
{
    QuadrupedRobot robot;
    for (;;) {
        std::cout << "введите имя, заряд (0-100), команду и дистанцию\n"
                  << "строки с пробелами заключайте в кавычки, пример: \"Арчи\" 80 \"идти вперёд\" 12.5\n";
        std::string name;
        std::string command;
        int battery = 0;
        double distance = 0.0;
        if (!(std::cin >> std::quoted(name) >> battery >> std::quoted(command) >> distance)) {
            if (std::cin.eof()) {
                return 1;
            }
            std::cout << "ошибка формата, повторите ввод\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try {
            robot.setState(name, battery, command, distance);
            break;
        } catch (const std::invalid_argument& error) {
            std::cout << "ошибка: " << error.what() << "; исправьте данные\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    robot.print();
    return 0;
}
