#include "human.h"

#include <iostream>

namespace book {
Human_basic::Human_basic() : name("John"), family_name("Doe")
{
    std::cout << "Human_basic: конструктор по умолчанию\n";
}

Human_basic::Human_basic(const std::string& name, const std::string& family_name)
    : name(name), family_name(family_name)
{
    std::cout << "Human_basic: инициализирующий конструктор\n";
}

Human_basic::~Human_basic()
{
    std::cout << "Human_basic: деструктор\n";
}

const std::string& Human_basic::get_family_name() const { return family_name; }

Human_alive::Human_alive(const std::string& name, const std::string& family_name,
                         unsigned birth_year)
    : Human_basic(name, family_name), birth_year(birth_year)
{
    std::cout << "Human_alive: инициализирующий конструктор\n";
}

Human_alive::~Human_alive()
{
    std::cout << "Human_alive: деструктор\n";
}

const std::string& Human_alive::get_name() const { return name; }
unsigned Human_alive::get_birth_year() const { return birth_year; }

Human_weighted::Human_weighted(const std::string& name, const std::string& family_name,
                               unsigned birth_year, double weight)
    : Human_alive(name, family_name, birth_year), weight(weight)
{
    std::cout << "Human_weighted: инициализирующий конструктор\n";
}

Human_weighted::~Human_weighted()
{
    std::cout << "Human_weighted: деструктор\n";
}

void Human_weighted::set_weight(double value)
{
    weight = value;
    std::cout << "Human_weighted::set_weight(double): " << weight << '\n';
}

void Human_weighted::set_weight(int value)
{
    weight = value;
    std::cout << "Human_weighted::set_weight(int): " << weight << '\n';
}

double Human_weighted::get_weight() const { return weight; }
}

namespace book {
std::string Human_basic::get_info() const
{
    return "Human_basic: " + get_family_name() + " " + name;
}

std::string Human_basic::get_static_info() const
{
    return Human_basic::get_info();
}

std::string Human_alive::get_info() const
{
    return "Human_alive: " + name + " " + get_family_name() + " " + std::to_string(birth_year);
}

std::string Human_alive::get_static_info() const
{
    return Human_alive::get_info();
}

std::string Human_weighted::get_info() const
{
    return "Human_weighted: " + name + " " + get_family_name() + " " + std::to_string(birth_year) + " " + std::to_string(weight);
}

std::string Human_weighted::get_static_info() const
{
    return Human_weighted::get_info();
}

}
