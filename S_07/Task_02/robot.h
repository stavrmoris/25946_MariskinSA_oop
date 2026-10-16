#pragma once

#include <cstddef>
#include <string>

class QuadrupedRobot {
private:
    static std::size_t next_id_;
    static constexpr std::size_t history_days_ = 10;
    static std::size_t object_count_;
    static const std::string class_name_;
    const std::string id_;
    std::string name_;
    int battery_;
    std::string command_;
    double distance_today_;
    double* distance_history_;

    void normalize();
    void log(const char* event) const;
    void checkDay(std::size_t day) const;

public:
    QuadrupedRobot();
    QuadrupedRobot(const std::string& name, int battery,
                   const std::string& command, double distance_today);
    QuadrupedRobot(const QuadrupedRobot& other);
    QuadrupedRobot& operator=(const QuadrupedRobot& other);
    ~QuadrupedRobot();

    const std::string& getId() const;
    const std::string& getName() const;
    int getBattery() const;
    const std::string& getCommand() const;
    double getDistanceToday() const;
    std::size_t getHistorySize() const;
    double getDistanceForDay(std::size_t day) const;

    void setName(const std::string& name);
    void setBattery(int battery);
    void setCommand(const std::string& command);
    void setDistanceToday(double distance);
    void setDistanceForDay(std::size_t day, double distance);
    void print() const;
    static std::size_t getObjectCount();
    static const std::string& getClassName();
};
