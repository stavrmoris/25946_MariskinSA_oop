#include "robot_squad.h"

#include <array>
#include <functional>
#include <iostream>
#include <stdexcept>

int main()
{
    RobotFactory factory("Завод квадропедальных роботов");
    RobotAdministrator administrator;
    {
        std::cout << "=== завод устанавливает параметры робота ===\n";
        Robot robot;
        const std::string id = robot.getId();
        const double history[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        factory.configure(robot, "Q-9", "Арчи", 90, "патруль", 12.5, history);
        std::cout << robot << '\n';

        std::cout << "\n=== дружественная функция: производитель ===\n";
        setManufacturer(robot, "Новый производитель");
        std::cout << robot << '\n';

        std::cout << "\n=== дружественный метод администратора: модель ===\n";
        administrator.setModel(robot, "Q-9 Pro");
        administrator.showModel(robot);
        std::cout << "id остался прежним: " << std::boolalpha << (id == robot.getId()) << '\n';
        try {
            administrator.setModel(robot, " ");
        } catch (const std::invalid_argument& error) {
            std::cout << "отклонено: " << error.what() << '\n';
        }
        std::cout << "модель после ошибки: " << robot.getModel() << '\n';
    }

    std::cout << "\n=== композиция: отделение само содержит 5 роботов ===\n";
    {
        OwnedRobotSquad squad(factory);
        std::cout << "в отделении: " << squad.size()
                  << " | живых роботов: " << Robot::getObjectCount() << '\n';
        squad.show();
    }
    std::cout << "отделение уничтожено, роботов осталось: " << Robot::getObjectCount() << '\n';

    std::cout << "\n=== агрегация: роботы существуют отдельно от отделения ===\n";
    {
        std::array<Robot, 5> external_robots;
        const double history[10]{};
        for (std::size_t i = 0; i < external_robots.size(); ++i) {
            factory.configure(external_robots[i], "Q-9", "Внешний-" + std::to_string(i + 1),
                              80, "стоп", 0.0, history);
        }
        const std::array<std::reference_wrapper<Robot>, 5> references{
            std::ref(external_robots[0]), std::ref(external_robots[1]),
            std::ref(external_robots[2]), std::ref(external_robots[3]), std::ref(external_robots[4])
        };
        {
            AggregatedRobotSquad first(references);
            AggregatedRobotSquad second(references);
            std::cout << "два отделения используют одних роботов, всего живых: "
                      << Robot::getObjectCount() << '\n';
            administrator.setModel(first.getRobot(0), "Общая модель");
            std::cout << "тот же робот во втором отделении: " << second.getRobot(0) << '\n';
            first.show();
        }
        std::cout << "отделения уничтожены, внешних роботов осталось: "
                  << Robot::getObjectCount() << '\n';
        external_robots[0].print();
    }
    std::cout << "после завершения всех блоков роботов: " << Robot::getObjectCount() << '\n';
    return 0;
}
