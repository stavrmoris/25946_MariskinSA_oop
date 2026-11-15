#pragma once

#include "human.h"

namespace book {
class Student_hidden : public Human_weighted {
public:
    using Human_weighted::Human_weighted;
    void set_weight(double value);
};

class Student : public Human_weighted {
public:
    using Human_weighted::Human_weighted;
    using Human_weighted::set_weight;
    Student(const std::string& name, const std::string& family_name,
            unsigned birth_year, double weight, const std::string& uni);
    ~Student();
    void set_weight(double value);
    std::string uni;
};

class Student_deleted : public Human_weighted {
public:
    using Human_weighted::Human_weighted;
    void set_weight(double value);
    void set_weight(int value) = delete;
};
}
