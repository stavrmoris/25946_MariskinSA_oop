#include "student.h"

#include <array>
#include <iostream>
#include <memory>

int main()
{
    book::Human_basic basic("Alexander", "Volkov");
    book::Human_alive alive("Alex", "Vol", 1991);
    book::Human_weighted weighted("Alex", "Vol", 1991, 60.5);
    book::Human_can_read reader("Alex", "Vol", 2002, 51.0, "прочитано");
    book::Human_can_write writer("Alex", "Vol", 2003, 58.0, "записано");
    book::Student student("Alex", "Vol", 2005, 71.0, "NSU", "прочитано", "записано");

    std::cout << "\n=== прямые вызовы ===\n";
    std::cout << basic.get_info() << '\n' << alive.get_info() << '\n'
              << weighted.get_info() << '\n' << reader.get_info() << '\n'
              << writer.get_info() << '\n' << student.get_info() << '\n';

    std::array<book::Human_basic*, 6> people{&basic, &alive, &weighted, &reader, &writer, &student};
    std::cout << "\n=== невиртуальный метод через базовый указатель ===\n";
    for (const book::Human_basic* person : people) {
        std::cout << person->get_static_info() << '\n';
    }

    std::cout << "\n=== виртуальный метод через те же указатели ===\n";
    for (const book::Human_basic* person : people) {
        std::cout << person->get_info() << '\n';
    }

    std::cout << "\n=== массив базовых объектов: срезка наследников ===\n";
    const std::array<book::Human_basic, 6> values{basic, alive, weighted, reader, writer, student};
    for (const book::Human_basic& person : values) {
        std::cout << person.get_info() << '\n';
    }

    std::cout << "\n=== виртуальный деструктор при удалении через базовый тип ===\n";
    {
        std::unique_ptr<book::Human_basic> owned = std::make_unique<book::Student>(
            "John", "Doe", 2000, 70.0, "NSU", "чтение", "запись");
        std::cout << owned->get_info() << '\n';
    }
    return 0;
}
