#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

namespace robot_detail {
inline std::string trimmedText(const std::string& text)
{
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}
}

template <typename Charge, typename Distance>
std::size_t QuadrupedRobot<Charge, Distance>::object_count_ = 0;
template <typename Charge, typename Distance>
const std::string QuadrupedRobot<Charge, Distance>::class_name_ = "QuadrupedRobot";

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>::QuadrupedRobot()
    : id_("robot-" + std::to_string(++robot_detail::next_id)), name_("робот"), battery_(100),
      command_("ожидание"), distance_today_(0.0), distance_history_(nullptr)
{
    normalize(name_, battery_, command_, distance_today_);
    distance_history_ = new Distance[history_days_]{};
    ++object_count_;
    log("конструктор по умолчанию");
}

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>::QuadrupedRobot(const std::string& name, Charge battery,
                             const std::string& command, Distance distance_today)
    : id_("robot-" + std::to_string(++robot_detail::next_id)), name_(name), battery_(battery),
      command_(command), distance_today_(distance_today), distance_history_(nullptr)
{
    normalize(name_, battery_, command_, distance_today_);
    distance_history_ = new Distance[history_days_]{};
    ++object_count_;
    log("инициализирующий конструктор");
}

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>::QuadrupedRobot(const QuadrupedRobot<Charge, Distance>& other)
    : id_("robot-" + std::to_string(++robot_detail::next_id)), name_(other.name_),
      battery_(other.battery_), command_(other.command_),
      distance_today_(other.distance_today_), distance_history_(nullptr)
{
    // копия владеет собственным массивом
    distance_history_ = new Distance[history_days_];
    for (std::size_t day = 0; day < history_days_; ++day) {
        distance_history_[day] = other.distance_history_ ? other.distance_history_[day] : Distance{};
    }
    ++object_count_;
    log("конструктор копирования");
}

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>::QuadrupedRobot(QuadrupedRobot<Charge, Distance>&& other)
    : id_("robot-" + std::to_string(++robot_detail::next_id)), name_("робот"),
      battery_(other.battery_), command_("ожидание"),
      distance_today_(other.distance_today_), distance_history_(other.distance_history_)
{
    name_.swap(other.name_);
    command_.swap(other.command_);
    // передаём владение массивом, исходный объект сохраняет свой id
    other.distance_history_ = nullptr;
    other.battery_ = 0;
    other.distance_today_ = Distance{};
    ++object_count_;
    log("конструктор перемещения");
}

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>& QuadrupedRobot<Charge, Distance>::operator=(const QuadrupedRobot<Charge, Distance>& other)
{
    if (this != &other) {
        std::string new_name(other.name_);
        std::string new_command(other.command_);
        // сначала готовим новую память, затем освобождаем старую
        Distance* new_history = new Distance[history_days_];
        for (std::size_t day = 0; day < history_days_; ++day) {
            new_history[day] = other.distance_history_ ? other.distance_history_[day] : Distance{};
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

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>& QuadrupedRobot<Charge, Distance>::operator=(QuadrupedRobot<Charge, Distance>&& other)
{
    if (this != &other) {
        delete[] distance_history_;
        distance_history_ = other.distance_history_;
        other.distance_history_ = nullptr;
        // источник получает прежние допустимые строки получателя
        name_.swap(other.name_);
        command_.swap(other.command_);
        battery_ = other.battery_;
        distance_today_ = other.distance_today_;
        other.battery_ = 0;
        other.distance_today_ = Distance{};
    }
    log("перемещающий оператор присваивания");
    return *this;
}

template <typename Charge, typename Distance>
QuadrupedRobot<Charge, Distance>::~QuadrupedRobot()
{
    delete[] distance_history_;
    --object_count_;
    log("деструктор");
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::normalize(std::string& name, Charge battery,
                               std::string& command, Distance distance)
{
    name = robot_detail::trimmedText(name);
    command = robot_detail::trimmedText(command);
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

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::log(const char* event) const
{
    std::cout << "[" << class_name_ << " | " << id_ << "] " << event
              << " | объектов: " << object_count_ << "\n";
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::checkDay(std::size_t day) const
{
    if (day >= history_days_) {
        throw std::out_of_range("номер дня должен быть от 0 до 9");
    }
}

template <typename Charge, typename Distance>
const std::string& QuadrupedRobot<Charge, Distance>::getId() const { return id_; }
template <typename Charge, typename Distance>
const std::string& QuadrupedRobot<Charge, Distance>::getName() const { return name_; }
template <typename Charge, typename Distance>
Charge QuadrupedRobot<Charge, Distance>::getBattery() const { return battery_; }
template <typename Charge, typename Distance>
const std::string& QuadrupedRobot<Charge, Distance>::getCommand() const { return command_; }
template <typename Charge, typename Distance>
Distance QuadrupedRobot<Charge, Distance>::getDistanceToday() const { return distance_today_; }
template <typename Charge, typename Distance>
std::size_t QuadrupedRobot<Charge, Distance>::getHistorySize() const { return history_days_; }

template <typename Charge, typename Distance>
Distance QuadrupedRobot<Charge, Distance>::getDistanceForDay(std::size_t day) const
{
    checkDay(day);
    return distance_history_ ? distance_history_[day] : Distance{};
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setState(const std::string& name, Charge battery,
                              const std::string& command, Distance distance)
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

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setName(const std::string& name)
{
    setState(name, battery_, command_, distance_today_);
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setBattery(Charge battery)
{
    setState(name_, battery, command_, distance_today_);
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setCommand(const std::string& command)
{
    setState(name_, battery_, command, distance_today_);
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setDistanceToday(Distance distance)
{
    setState(name_, battery_, command_, distance);
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::setDistanceForDay(std::size_t day, Distance distance)
{
    checkDay(day);
    if (!std::isfinite(distance) || distance < 0.0) {
        throw std::invalid_argument("дистанция должна быть конечной и неотрицательной");
    }
    if (distance_history_ == nullptr) {
        distance_history_ = new Distance[history_days_]{};
    }
    distance_history_[day] = distance;
}

template <typename Charge, typename Distance>
void QuadrupedRobot<Charge, Distance>::print() const
{
    std::cout << "--- робот " << id_ << " ---\n"
              << "имя: " << name_ << " | заряд: " << battery_ << "%\n"
              << "команда: " << command_ << " | дистанция за сегодня: "
              << distance_today_ << " м\nистория за последние 10 дней (м):";
    for (std::size_t day = 0; day < history_days_; ++day) {
        std::cout << ' ' << getDistanceForDay(day);
    }
    std::cout << "\n--------------------\n";
}

template <typename Charge, typename Distance>
std::size_t QuadrupedRobot<Charge, Distance>::getObjectCount() { return object_count_; }
template <typename Charge, typename Distance>
const std::string& QuadrupedRobot<Charge, Distance>::getClassName() { return class_name_; }


template <typename Charge, typename Distance>
std::ostream& operator<<(std::ostream& output, const QuadrupedRobot<Charge, Distance>& robot)
{
    output << QuadrupedRobot<Charge, Distance>::getClassName() << " | id: " << robot.getId()
           << " | объектов: " << QuadrupedRobot<Charge, Distance>::getObjectCount()
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

template <typename Charge, typename Distance>
std::istream& operator>>(std::istream& input, QuadrupedRobot<Charge, Distance>& robot)
{
    std::string name;
    std::string command;
    Charge battery = 0;
    Distance distance = 0.0;
    if (input >> std::quoted(name) >> battery >> std::quoted(command) >> distance) {
        robot.setState(name, battery, command, distance);
    }
    return input;
}
