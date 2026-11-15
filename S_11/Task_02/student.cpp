#include "student.h"

#include <iostream>

namespace ordinary {
Human_can_read::Human_can_read(const std::string& name, const std::string& family_name,
                               unsigned birth_year, double weight, const std::string& text)
    : book::Human_weighted(name, family_name, birth_year, weight), readed_text(text)
{
    std::cout << "ordinary::Human_can_read: инициализирующий конструктор\n";
}

Human_can_read::~Human_can_read()
{
    std::cout << "ordinary::Human_can_read: деструктор\n";
}

std::string Human_can_read::read(const std::string& text)
{
    readed_text = text;
    return readed_text;
}

Human_can_write::Human_can_write(const std::string& name, const std::string& family_name,
                                 unsigned birth_year, double weight, const std::string& text)
    : book::Human_weighted(name, family_name, birth_year, weight), written_text(text)
{
    std::cout << "ordinary::Human_can_write: инициализирующий конструктор\n";
}

Human_can_write::~Human_can_write()
{
    std::cout << "ordinary::Human_can_write: деструктор\n";
}

void Human_can_write::write(const std::string& text)
{
    written_text = text;
}

const std::string& Human_can_write::get_written_text() const { return written_text; }

Student::Student(const std::string& name, const std::string& family_name,
                 unsigned birth_year, double weight, const std::string& uni,
                 const std::string& readed_text, const std::string& written_text)
    : Human_can_read(name, family_name, birth_year, weight, readed_text),
      Human_can_write(name, family_name, birth_year, weight, written_text), uni(uni)
{
    std::cout << "ordinary::Student: инициализирующий конструктор\n";
}

Student::~Student()
{
    std::cout << "ordinary::Student из " << uni << ": деструктор\n";
}
}

namespace book {
Human_can_read::Human_can_read(const std::string& name, const std::string& family_name,
                               unsigned birth_year, double weight, const std::string& text)
    : book::Human_weighted(name, family_name, birth_year, weight), readed_text(text)
{
    std::cout << "book::Human_can_read: инициализирующий конструктор\n";
}

Human_can_read::~Human_can_read()
{
    std::cout << "book::Human_can_read: деструктор\n";
}

std::string Human_can_read::read(const std::string& text)
{
    readed_text = text;
    return readed_text;
}

Human_can_write::Human_can_write(const std::string& name, const std::string& family_name,
                                 unsigned birth_year, double weight, const std::string& text)
    : book::Human_weighted(name, family_name, birth_year, weight), written_text(text)
{
    std::cout << "book::Human_can_write: инициализирующий конструктор\n";
}

Human_can_write::~Human_can_write()
{
    std::cout << "book::Human_can_write: деструктор\n";
}

void Human_can_write::write(const std::string& text)
{
    written_text = text;
}

const std::string& Human_can_write::get_written_text() const { return written_text; }

Student::Student(const std::string& name, const std::string& family_name,
                 unsigned birth_year, double weight, const std::string& uni,
                 const std::string& readed_text, const std::string& written_text)
    : book::Human_weighted(name, family_name, birth_year, weight),
      Human_can_read(name, family_name, birth_year, weight, readed_text),
      Human_can_write(name, family_name, birth_year, weight, written_text), uni(uni)
{
    std::cout << "book::Student: инициализирующий конструктор\n";
}

Student::~Student()
{
    std::cout << "book::Student из " << uni << ": деструктор\n";
}
}

