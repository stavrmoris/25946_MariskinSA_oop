#include "human.h"

#include <iostream>

int main()
{
    std::cout << "=== базовый класс ===\n";
    book::Human_basic basic_default;
    book::Human_basic basic("Alexander", "Volkov");
    std::cout << basic_default.get_family_name() << ' ' << basic.get_family_name() << '\n';

    std::cout << "\n=== public наследование и protected поля ===\n";
    book::Human_alive alive_default;
    book::Human_alive alive("Alex", "Volk", 1933);
    std::cout << alive.get_name() << ' ' << alive.get_family_name()
              << ' ' << alive.get_birth_year() << '\n';
    std::cout << "год по умолчанию: " << alive_default.get_birth_year() << '\n';
    // alive.name; // поле protected доступно наследнику, но не main

    std::cout << "\n=== унаследованный конструктор с двумя аргументами ===\n";
    book::Human_alive inherited("Ale", "Vol");
    std::cout << inherited.get_name() << ' ' << inherited.get_family_name()
              << ' ' << inherited.get_birth_year() << '\n';

    std::cout << "\n=== final private наследование и доступ через using ===\n";
    book::Human_dead dead("Alexander", "Volkov", 1891, 1977);
    book::Human_dead dead_default;
    book::Human_dead dead_inherited("John", "Smith");
    std::cout << dead.get_name() << ' ' << dead.get_family_name()
              << ' ' << dead.get_birth_year() << '-' << dead.get_death_year() << '\n';
    std::cout << dead_default.get_name() << ' ' << dead_inherited.get_family_name() << '\n';
    // class Zombie : public book::Human_dead {}; // final запрещает наследование
    // book::Human_alive& parent = dead; // private запрещает внешнее преобразование

    std::cout << "\n=== уничтожение в обратном порядке ===\n";
    return 0;
}
