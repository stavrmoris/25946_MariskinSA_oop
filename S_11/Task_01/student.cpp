#include "student.h"

#include <iostream>

namespace book {
void Student_hidden::set_weight(double value)
{
    weight = value;
    std::cout << "Student_hidden::set_weight(double): " << weight << '\n';
}

Student::Student(const std::string& name, const std::string& family_name,
                 unsigned birth_year, double weight, const std::string& uni)
    : Human_weighted(name, family_name, birth_year, weight), uni(uni)
{
    std::cout << "Student: инициализирующий конструктор\n";
}

Student::~Student()
{
    std::cout << "Student из " << uni << ": деструктор\n";
}

void Student::set_weight(double value)
{
    weight = value;
    std::cout << "Student::set_weight(double): " << weight << '\n';
}

void Student_deleted::set_weight(double value)
{
    weight = value;
    std::cout << "Student_deleted::set_weight(double): " << weight << '\n';
}
}
