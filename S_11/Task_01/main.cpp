#include "student.h"

#include <iostream>

int main()
{
    std::cout << "=== перегрузки базового класса ===\n";
    book::Human_weighted human_default;
    book::Human_weighted human("Alex", "Vol", 1991, 50.0);
    human.set_weight(41);
    human.set_weight(42.2);
    std::cout << "масса по умолчанию: " << human_default.get_weight() << '\n';

    std::cout << "\n=== скрытие перегрузок родителя ===\n";
    book::Student_hidden hidden("Alex", "Vol", 2002, 51.0);
    hidden.set_weight(61);
    hidden.set_weight(62.2);

    std::cout << "\n=== using возвращает перегрузку int ===\n";
    book::Student student_default;
    book::Student student("Alex", "Vol", 2002, 51.0, "NSU");
    student_default.set_weight(61);
    student.set_weight(62.2);
    std::cout << student.get_name() << ' ' << student.uni
              << " | масса: " << student.get_weight() << '\n';

    std::cout << "\n=== delete запрещает вызов с int ===\n";
    book::Student_deleted limited("Alex", "Vol", 2002, 51.0);
    limited.set_weight(62.2);
    // limited.set_weight(61); // вызов удалённой функции не компилируется
    limited.set_weight(static_cast<double>(61));

    std::cout << "\n=== уничтожение ===\n";
    return 0;
}
