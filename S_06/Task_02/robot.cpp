#include "robot.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
std::string normalizedText(const std::string& text, const std::string& fallback)
{
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return fallback;
    }
    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

double normalizedDistance(double distance)
{
    return std::isfinite(distance) && distance >= 0.0 ? distance : 0.0;
}
}

std::size_t QuadrupedRobot::next_id_ = 0;

QuadrupedRobot::QuadrupedRobot()
    : id_("robot-" + std::to_string(++next_id_)), name_("робот"), battery_(100),
      command_("ожидание"), distance_today_(0.0), distance_history_{}
{
    normalize();

    log("конструктор по умолчанию");
}

QuadrupedRobot::QuadrupedRobot(const std::string& name, int battery,
                             const std::string& command, double distance_today)
    : id_("robot-" + std::to_string(++next_id_)), name_(name), battery_(battery),
      command_(command), distance_today_(distance_today), distance_history_{}
{
    normalize();

    log("инициализирующий конструктор");
}

QuadrupedRobot::QuadrupedRobot(const QuadrupedRobot& other)
    : id_("robot-" + std::to_string(++next_id_)), name_(other.name_),
      battery_(other.battery_), command_(other.command_),
      distance_today_(other.distance_today_), distance_history_{}
{
    for (std::size_t day = 0; day < history_days_; ++day) {
        distance_history_[day] = other.distance_history_[day];
    }

    log("конструктор копирования");
}

QuadrupedRobot& QuadrupedRobot::operator=(const QuadrupedRobot& other)
{
    if (this != &other) {
        std::string new_name(other.name_);
        std::string new_command(other.command_);
        for (std::size_t day = 0; day < history_days_; ++day) {
            distance_history_[day] = other.distance_history_[day];
        }
        name_.swap(new_name);
        command_.swap(new_command);
        battery_ = other.battery_;
        distance_today_ = other.distance_today_;
    }
    // присваивание меняет данные существующего робота, но сохраняет его id
    log("оператор присваивания");
    return *this;
}

QuadrupedRobot::~QuadrupedRobot()
{
    log("деструктор");
}

void QuadrupedRobot::normalize()
{
    name_ = normalizedText(name_, "робот");
    command_ = normalizedText(command_, "ожидание");
    battery_ = std::clamp(battery_, 0, 100);
    distance_today_ = normalizedDistance(distance_today_);
}

void QuadrupedRobot::log(const char* event) const
{
    std::cout << "[" << id_ << "] " << event << '\n';
}

void QuadrupedRobot::checkDay(std::size_t day) const
{
    if (day >= history_days_) {
        throw std::out_of_range("номер дня должен быть от 0 до 9");
    }
}

const std::string& QuadrupedRobot::getId() const { return id_; }
const std::string& QuadrupedRobot::getName() const { return name_; }
int QuadrupedRobot::getBattery() const { return battery_; }
const std::string& QuadrupedRobot::getCommand() const { return command_; }
double QuadrupedRobot::getDistanceToday() const { return distance_today_; }
std::size_t QuadrupedRobot::getHistorySize() const { return history_days_; }

double QuadrupedRobot::getDistanceForDay(std::size_t day) const
{
    checkDay(day);
    return distance_history_[day];
}

void QuadrupedRobot::setName(const std::string& name)
{
    name_ = normalizedText(name, "робот");
}

void QuadrupedRobot::setBattery(int battery)
{
    battery_ = std::clamp(battery, 0, 100);
}

void QuadrupedRobot::setCommand(const std::string& command)
{
    command_ = normalizedText(command, "ожидание");
}

void QuadrupedRobot::setDistanceToday(double distance)
{
    distance_today_ = normalizedDistance(distance);
}

void QuadrupedRobot::setDistanceForDay(std::size_t day, double distance)
{
    checkDay(day);
    distance_history_[day] = normalizedDistance(distance);
}

void QuadrupedRobot::print() const
{
    std::cout << "--- робот " << id_ << " ---\n"
              << "имя: " << name_ << " | заряд: " << battery_ << "%\n"
              << "команда: " << command_ << " | дистанция за сегодня: "
              << distance_today_ << " м\nистория за последние 10 дней (м):";
    for (std::size_t day = 0; day < history_days_; ++day) {
        std::cout << ' ' << distance_history_[day];
    }
    std::cout << "\n--------------------\n";
}

