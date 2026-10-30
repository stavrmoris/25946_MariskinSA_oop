#include "robot.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace {
std::string trimmedText(const std::string& text)
{
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}
}

std::size_t QuadrupedRobot::next_id_ = 0;
std::size_t QuadrupedRobot::object_count_ = 0;
const std::string QuadrupedRobot::class_name_ = "QuadrupedRobot";

QuadrupedRobot::QuadrupedRobot()
    : id_("robot-" + std::to_string(++next_id_)), name_("робот"), battery_(100),
      command_("ожидание"), distance_today_(0.0), distance_history_(nullptr)
{
    normalize(name_, battery_, command_, distance_today_);
    distance_history_ = new double[history_days_]{};
    ++object_count_;
    log("конструктор по умолчанию");
}

QuadrupedRobot::QuadrupedRobot(const std::string& name, int battery,
                             const std::string& command, double distance_today)
    : id_("robot-" + std::to_string(++next_id_)), name_(name), battery_(battery),
      command_(command), distance_today_(distance_today), distance_history_(nullptr)
{
    normalize(name_, battery_, command_, distance_today_);
    distance_history_ = new double[history_days_]{};
    ++object_count_;
    log("инициализирующий конструктор");
}

QuadrupedRobot::QuadrupedRobot(const QuadrupedRobot& other)
    : id_("robot-" + std::to_string(++next_id_)), name_(other.name_),
      battery_(other.battery_), command_(other.command_),
      distance_today_(other.distance_today_), distance_history_(nullptr)
{
    // копия владеет собственным массивом
    distance_history_ = new double[history_days_];
    for (std::size_t day = 0; day < history_days_; ++day) {
        distance_history_[day] = other.distance_history_[day];
    }
    ++object_count_;
    log("конструктор копирования");
}

QuadrupedRobot& QuadrupedRobot::operator=(const QuadrupedRobot& other)
{
    if (this != &other) {
        std::string new_name(other.name_);
        std::string new_command(other.command_);
        // сначала готовим новую память, затем освобождаем старую
        double* new_history = new double[history_days_];
        for (std::size_t day = 0; day < history_days_; ++day) {
            new_history[day] = other.distance_history_[day];
        }
        delete[] distance_history_;
        distance_history_ = new_history;
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
    delete[] distance_history_;
    --object_count_;
    log("деструктор");
}

void QuadrupedRobot::normalize(std::string& name, int battery,
                               std::string& command, double distance)
{
    name = trimmedText(name);
    command = trimmedText(command);
    if (name.empty()) {
        throw std::invalid_argument("имя не должно быть пустым");
    }
    if (command.empty()) {
        throw std::invalid_argument("команда не должна быть пустой");
    }
    if (battery < 0 || battery > 100) {
        throw std::invalid_argument("заряд должен быть от 0 до 100");
    }
    if (!std::isfinite(distance) || distance < 0.0) {
        throw std::invalid_argument("дистанция должна быть конечной и неотрицательной");
    }
}

void QuadrupedRobot::log(const char* event) const
{
    std::cout << "[" << class_name_ << " | " << id_ << "] " << event
              << " | объектов: " << object_count_ << "\n";
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

void QuadrupedRobot::setState(const std::string& name, int battery,
                              const std::string& command, double distance)
{
    std::string new_name(name);
    std::string new_command(command);
    // проверяем новые данные до изменения существующего объекта
    normalize(new_name, battery, new_command, distance);
    name_.swap(new_name);
    command_.swap(new_command);
    battery_ = battery;
    distance_today_ = distance;
}

void QuadrupedRobot::setName(const std::string& name)
{
    setState(name, battery_, command_, distance_today_);
}

void QuadrupedRobot::setBattery(int battery)
{
    setState(name_, battery, command_, distance_today_);
}

void QuadrupedRobot::setCommand(const std::string& command)
{
    setState(name_, battery_, command, distance_today_);
}

void QuadrupedRobot::setDistanceToday(double distance)
{
    setState(name_, battery_, command_, distance);
}

void QuadrupedRobot::setDistanceForDay(std::size_t day, double distance)
{
    checkDay(day);
    if (!std::isfinite(distance) || distance < 0.0) {
        throw std::invalid_argument("дистанция должна быть конечной и неотрицательной");
    }
    distance_history_[day] = distance;
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

std::size_t QuadrupedRobot::getObjectCount() { return object_count_; }
const std::string& QuadrupedRobot::getClassName() { return class_name_; }


std::ostream& operator<<(std::ostream& output, const QuadrupedRobot& robot)
{
    output << QuadrupedRobot::getClassName() << " | id: " << robot.getId()
           << " | объектов: " << QuadrupedRobot::getObjectCount()
           << " | имя: " << std::quoted(robot.getName())
           << " | заряд: " << robot.getBattery()
           << " | команда: " << std::quoted(robot.getCommand())
           << " | сегодня: " << robot.getDistanceToday()
           << " | история:";
    for (std::size_t day = 0; day < robot.getHistorySize(); ++day) {
        output << ' ' << robot.getDistanceForDay(day);
    }
    return output;
}

std::istream& operator>>(std::istream& input, QuadrupedRobot& robot)
{
    std::string name;
    std::string command;
    int battery = 0;
    double distance = 0.0;
    if (input >> std::quoted(name) >> battery >> std::quoted(command) >> distance) {
        robot.setState(name, battery, command, distance);
    }
    return input;
}
