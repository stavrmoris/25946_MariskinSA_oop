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
    virtual ~Human_basic();
    virtual std::string get_info() const;
    std::string get_static_info() const;
    const std::string& get_family_name() const;
};

class Human_alive : public Human_basic {
protected:
    unsigned birth_year = 0;

public:
    using Human_basic::Human_basic;
    Human_alive(const std::string& name, const std::string& family_name, unsigned birth_year);
    ~Human_alive() override;
    std::string get_info() const override;
    std::string get_static_info() const;
    const std::string& get_name() const;
    unsigned get_birth_year() const;
};

class Human_weighted : public Human_alive {
protected:
    double weight = 0.0;

public:
    using Human_alive::Human_alive;
    Human_weighted(const std::string& name, const std::string& family_name,
                   unsigned birth_year, double weight);
    ~Human_weighted() override;
    std::string get_info() const override;
    std::string get_static_info() const;
    void set_weight(double value);
    void set_weight(int value);
    double get_weight() const;
};
}
