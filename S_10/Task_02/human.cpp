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

Human_dead::Human_dead(const std::string& name, const std::string& family_name,
                       unsigned birth_year, unsigned death_year)
    : Human_alive(name, family_name, birth_year), death_year(death_year)
{
    std::cout << "Human_dead: инициализирующий конструктор\n";
}

Human_dead::~Human_dead()
{
    std::cout << "Human_dead: деструктор\n";
}

unsigned Human_dead::get_death_year() const { return death_year; }
}
