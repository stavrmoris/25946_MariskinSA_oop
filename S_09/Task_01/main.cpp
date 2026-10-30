#include "robot.h"

#include <iostream>
#include <stdexcept>
#include <utility>

using Robot = QuadrupedRobot<int, double>;

int main()
{
    std::cout << "=== внешняя станция создаётся независимо ===\n";
    ControlStation station("Станция-1");
    RobotTechnician technician;
    RobotInspector inspector;
    {
        Robot first("Арчи", 40, "вперёд", 12.5);
        first.setDistanceForDay(0, 10.0);
        std::cout << first << '\n';

        std::cout << "\n=== дружественная свободная функция ===\n";
        renameRobot(first, "  Рекс  ");
        std::cout << first << '\n';
        try {
            renameRobot(first, " ");
        } catch (const std::invalid_argument& error) {
            std::cout << "ошибка: " << error.what() << '\n';
        }
        std::cout << "имя после отклонённого изменения: " << first.getName() << '\n';

        std::cout << "\n=== дружественный класс ===\n";
        technician.recharge(first, 95);
        technician.resetToday(first);
        technician.addServiceEntry(first, "зарядка и осмотр");
        std::cout << first << '\n';

        std::cout << "\n=== только отдельный метод класса является другом ===\n";
        inspector.clearHistory(first);
        inspector.describe(first, std::cout);
        std::cout << first << '\n';

        std::cout << "\n=== композиция: собственный журнал каждого робота ===\n";
        Robot second(first);
        technician.addServiceEntry(first, "проверка приводов");
        std::cout << "журнал первого: " << first.getMaintenanceLog().getEntryCount()
                  << " | последняя запись: " << first.getMaintenanceLog().getLastEntry() << '\n';
        std::cout << "журнал копии: " << second.getMaintenanceLog().getEntryCount()
                  << " | последняя запись: " << second.getMaintenanceLog().getLastEntry() << '\n';
        std::cout << "журналы разные: " << std::boolalpha
                  << (&first.getMaintenanceLog() != &second.getMaintenanceLog()) << '\n';

        std::cout << "\n=== агрегация: общая внешняя станция ===\n";
        technician.connect(first, station);
        technician.connect(second, station);
        std::cout << "станция одна: " << (first.getStation() == second.getStation()) << '\n';
        station.setName("Общая станция");
        std::cout << first << '\n' << second << '\n';
        technician.disconnect(second);
        std::cout << "второй отключён: " << second << '\n';

        std::cout << "\n=== копирование и перемещение с компонентами ===\n";
        second = first;
        Robot moved(std::move(second));
        std::cout << moved << '\n';
        second = std::move(moved);
        std::cout << second << '\n';
        std::cout << "\n=== уничтожение роботов и их журналов ===\n";
    }
    std::cout << "роботов осталось: " << Robot::getObjectCount() << '\n';
    std::cout << "внешняя станция продолжает существовать: " << station.getName() << '\n';
    return 0;
}
