#pragma once

#include <string>

namespace book {
class Human_basic {
protected:
    std::string name;
    std::string family_name;

public:
    Human_basic();
    Human_basic(const std::string& name, const std::string& family_name);
    ~Human_basic();
    const std::string& get_family_name() const;
};

class Human_alive : public Human_basic {
protected:
    unsigned birth_year = 0;

public:
    using Human_basic::Human_basic;
    Human_alive(const std::string& name, const std::string& family_name, unsigned birth_year);
    ~Human_alive();
    const std::string& get_name() const;
    unsigned get_birth_year() const;
};

class Human_dead final : private Human_alive {
protected:
    unsigned death_year = 0;

public:
    using Human_alive::Human_alive;
    using Human_basic::get_family_name;
    using Human_alive::get_name;
    using Human_alive::get_birth_year;
    Human_dead(const std::string& name, const std::string& family_name,
               unsigned birth_year, unsigned death_year);
    ~Human_dead();
    unsigned get_death_year() const;
};
}
