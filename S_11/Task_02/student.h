#pragma once

#include "human.h"

namespace ordinary {
class Human_can_read : public book::Human_weighted {
protected:
    std::string readed_text;

public:
    using book::Human_weighted::Human_weighted;
    Human_can_read(const std::string& name, const std::string& family_name,
                   unsigned birth_year, double weight, const std::string& text);
    ~Human_can_read();
    std::string read(const std::string& text);
};

class Human_can_write : public book::Human_weighted {
protected:
    std::string written_text;

public:
    using book::Human_weighted::Human_weighted;
    Human_can_write(const std::string& name, const std::string& family_name,
                    unsigned birth_year, double weight, const std::string& text);
    ~Human_can_write();
    void write(const std::string& text);
    const std::string& get_written_text() const;
};

class Student : public Human_can_read, public Human_can_write {
public:
    Student() = default;
    Student(const std::string& name, const std::string& family_name,
            unsigned birth_year, double weight, const std::string& uni,
            const std::string& readed_text, const std::string& written_text);
    ~Student();
    std::string uni;
};
}

namespace book {
class Human_can_read : public virtual book::Human_weighted {
protected:
    std::string readed_text;

public:
    using book::Human_weighted::Human_weighted;
    Human_can_read(const std::string& name, const std::string& family_name,
                   unsigned birth_year, double weight, const std::string& text);
    ~Human_can_read();
    std::string read(const std::string& text);
};

class Human_can_write : public virtual book::Human_weighted {
protected:
    std::string written_text;

public:
    using book::Human_weighted::Human_weighted;
    Human_can_write(const std::string& name, const std::string& family_name,
                    unsigned birth_year, double weight, const std::string& text);
    ~Human_can_write();
    void write(const std::string& text);
    const std::string& get_written_text() const;
};

class Student : public Human_can_read, public Human_can_write {
public:
    Student() = default;
    Student(const std::string& name, const std::string& family_name,
            unsigned birth_year, double weight, const std::string& uni,
            const std::string& readed_text, const std::string& written_text);
    ~Student();
    std::string uni;
};
}

