#include "robot.h"
#include <iostream>
#include <list>
#include <set>
#include <vector>

struct RobotById {
    bool operator()(const QuadrupedRobot& left, const QuadrupedRobot& right) const
    {
        return left.getId() < right.getId();
    }
};

int main()
{
    std::cout << "=== vector: копирование при добавлении и перераспределении памяти ===\n";
    {
        std::vector<QuadrupedRobot> robots;
        for (int i = 0; i < 4; ++i) {
            const QuadrupedRobot source("Вектор-" + std::to_string(i), 80, "стоп", i);
            robots.push_back(source);
            std::cout << "элементов: " << robots.size()
                      << " | ёмкость: " << robots.capacity()
                      << " | объектов вместе с источником: "
                      << QuadrupedRobot::getObjectCount() << '\n';
        }
        std::cout << "после цикла объектов: " << QuadrupedRobot::getObjectCount() << '\n';
    }
    std::cout << "после vector объектов: " << QuadrupedRobot::getObjectCount() << '\n';

    std::cout << "\n=== list: создание сразу в узлах ===\n";
    {
        std::list<QuadrupedRobot> robots;
        for (int i = 0; i < 4; ++i) {
            robots.emplace_back("Список-" + std::to_string(i), 80, "стоп", i);
            std::cout << "элементов: " << robots.size()
                      << " | объектов: " << QuadrupedRobot::getObjectCount() << '\n';
        }
    }
    std::cout << "после list объектов: " << QuadrupedRobot::getObjectCount() << '\n';

    std::cout << "\n=== set: создание сразу в узлах, порядок по id ===\n";
    {
        std::set<QuadrupedRobot, RobotById> robots;
        for (int i = 0; i < 4; ++i) {
            robots.emplace("Множество-" + std::to_string(i), 80, "стоп", i);
            std::cout << "элементов: " << robots.size()
                      << " | объектов: " << QuadrupedRobot::getObjectCount() << '\n';
        }
    }
    std::cout << "после set объектов: " << QuadrupedRobot::getObjectCount() << '\n';
    return 0;
}
