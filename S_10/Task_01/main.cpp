#include "autonomous_cargo_robot.h"

#include <iostream>
#include <stdexcept>

int main()
{
    {
        std::cout << "=== базовый робот ===\n";
        QuadrupedRobot base("Арчи", 80, "стоп", 3.0);
        base.setManufacturer("Завод роботов");
        base.setModel("Q-10");
        std::cout << base << '\n';

        std::cout << "\n=== public наследование: грузовой робот ===\n";
        CargoRobot cargo("Грузовик", 90, "доставка", 10.0, 45.0);
        cargo.setModel("Cargo-10");
        cargo.print();
        cargo.show_weight();
        cargo.setCargoWeight(CargoRobot::getMaxCargoWeight());
        cargo.show_weight();
        try {
            cargo.setCargoWeight(CargoRobot::getMaxCargoWeight() + 1.0);
        } catch (const std::invalid_argument& error) {
            std::cout << "груз отклонён: " << error.what() << '\n';
        }
        cargo.show_weight();

        std::cout << "\n=== final private наследование и публичный show_weight ===\n";
        AutonomousCargoRobot autonomous("Автономный", 100, "доставка", 0.0, 30.0);
        autonomous.show_weight();
        for (int i = 0; i < 8; ++i) {
            autonomous.showMode();
        }
        std::cout << "\n=== удаление: сначала наследник, затем базовые части ===\n";
    }
    std::cout << "живых роботов: " << QuadrupedRobot::getObjectCount() << '\n';
    return 0;
}
