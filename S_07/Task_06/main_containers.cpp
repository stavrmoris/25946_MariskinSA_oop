#include "robot.h"
#include <iostream>
#include <list>
#include <set>
#include <vector>

using Robot = QuadrupedRobot<int, double>;

struct RobotById {
    bool operator()(const Robot& left, const Robot& right) const
    {
        return left.getId() < right.getId();
    }
};

int main()
{
    std::cout << "=== vector: копирование при добавлении и перераспределении памяти ===\n";
    {
        std::vector<Robot> robots;
        for (int i = 0; i < 4; ++i) {
            const Robot source("Вектор-" + std::to_string(i), 80, "стоп", i);
            robots.push_back(source);
            std::cout << "элементов: " << robots.size()
                      << " | ёмкость: " << robots.capacity()
                      << " | объектов вместе с источником: "
                      << Robot::getObjectCount() << '\n';
        }
        std::cout << "после цикла объектов: " << Robot::getObjectCount() << '\n';
    }
    std::cout << "после vector объектов: " << Robot::getObjectCount() << '\n';

    std::cout << "\n=== list: создание сразу в узлах ===\n";
    {
        std::list<Robot> robots;
        for (int i = 0; i < 4; ++i) {
            robots.emplace_back("Список-" + std::to_string(i), 80, "стоп", i);
            std::cout << "элементов: " << robots.size()
                      << " | объектов: " << Robot::getObjectCount() << '\n';
        }
    }
    std::cout << "после list объектов: " << Robot::getObjectCount() << '\n';

    std::cout << "\n=== set: создание сразу в узлах, порядок по id ===\n";
    {
        std::set<Robot, RobotById> robots;
        for (int i = 0; i < 4; ++i) {
            robots.emplace("Множество-" + std::to_string(i), 80, "стоп", i);
            std::cout << "элементов: " << robots.size()
                      << " | объектов: " << Robot::getObjectCount() << '\n';
        }
    }
    std::cout << "после set объектов: " << Robot::getObjectCount() << '\n';
    return 0;
}
