#include "student.h"

#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    {
        std::cout << "=== обычное наследование: две базовые части ===\n";
        ordinary::Student student("Alex", "Vol", 1891, 71.0, "MIT", "прочитано", "записано");
        ordinary::Human_can_read& reader = student;
        ordinary::Human_can_write& writer = student;
        const book::Human_weighted* read_base = &reader;
        const book::Human_weighted* write_base = &writer;
        std::cout << "общая базовая часть: " << (read_base == write_base) << '\n';
        reader.set_weight(80.0);
        std::cout << "масса через чтение: " << reader.get_weight()
                  << " | через запись: " << writer.get_weight() << '\n';
        std::cout << student.read("текст из main") << '\n';
        student.write("новая запись");
        std::cout << student.get_written_text() << '\n';
        // student.get_birth_year(); // неоднозначно, существуют две базовые части
        std::cout << "=== уничтожение обычного ромба ===\n";
    }
    {
        std::cout << "\n=== virtual наследование: одна базовая часть ===\n";
        book::Student student("Alex", "Vol", 1891, 71.0, "MIT", "прочитано", "записано");
        book::Human_can_read& reader = student;
        book::Human_can_write& writer = student;
        const book::Human_weighted* read_base = &reader;
        const book::Human_weighted* write_base = &writer;
        std::cout << "общая базовая часть: " << (read_base == write_base) << '\n';
        std::cout << student.get_name() << ' ' << student.get_family_name()
                  << " | год: " << student.get_birth_year()
                  << " | масса: " << student.get_weight() << '\n';
        reader.set_weight(80.0);
        std::cout << "масса через чтение: " << reader.get_weight()
                  << " | через запись: " << writer.get_weight() << '\n';
        std::cout << student.read("текст из main") << '\n';
        std::cout << student.get_written_text() << '\n';
        student.write("новая запись");
        std::cout << student.get_written_text() << '\n';
        std::cout << "=== уничтожение виртуального ромба ===\n";
    }
    {
        std::cout << "\n=== конструкторы по умолчанию и отдельные ветви ===\n";
        book::Student student;
        std::cout << student.get_name() << " | год: " << student.get_birth_year()
                  << " | масса: " << student.get_weight() << '\n';
        book::Human_can_read reader("Alex", "Vol", 1991, 70.0, "прочитано");
        book::Human_can_write writer("John", "Doe", 2000, 65.0, "записано");
        std::cout << "год читающего: " << reader.get_birth_year()
                  << " | масса пишущего: " << writer.get_weight() << '\n';
    }
    return 0;
}
