#pragma once

#include <cstddef>
#include <iosfwd>
#include <type_traits>
#include <string>

#include "control_station.h"
#include "maintenance_log.h"
#include "robot_access.h"

namespace robot_detail {
inline std::size_t next_id = 0;
}

template <typename Charge, typename Distance>
class QuadrupedRobot {
    static_assert(std::is_integral_v<Charge> && std::is_signed_v<Charge>,
                  "тип заряда должен быть знаковым целочисленным");
    static_assert(std::is_floating_point_v<Distance>,
                  "тип дистанции должен быть вещественным");
private:
    static constexpr std::size_t history_days_ = 10;
    static std::size_t object_count_;
    static const std::string class_name_;
    const std::string id_;
    std::string name_;
    Charge battery_;
    std::string command_;
    Distance distance_today_;
    Distance* distance_history_;
    MaintenanceLog maintenance_;
    ControlStation* station_;

    friend void renameRobot<Charge, Distance>(QuadrupedRobot& robot, const std::string& name);
    friend class RobotTechnician;
    friend void RobotInspector::clearHistory<Charge, Distance>(QuadrupedRobot<Charge, Distance>& robot) const;

    static void normalize(std::string& name, Charge battery,
                          std::string& command, Distance distance);
    void setState(const std::string& name, Charge battery,
                  const std::string& command, Distance distance);
    void log(const char* event) const;
    void checkDay(std::size_t day) const;

public:
    QuadrupedRobot();
    QuadrupedRobot(const std::string& name, Charge battery,
                   const std::string& command, Distance distance_today);
    QuadrupedRobot(const QuadrupedRobot& other);
    QuadrupedRobot(QuadrupedRobot&& other);
    QuadrupedRobot& operator=(const QuadrupedRobot& other);
    QuadrupedRobot& operator=(QuadrupedRobot&& other);
    ~QuadrupedRobot();

    const std::string& getId() const;
    const std::string& getName() const;
    Charge getBattery() const;
    const std::string& getCommand() const;
    Distance getDistanceToday() const;
    std::size_t getHistorySize() const;
    Distance getDistanceForDay(std::size_t day) const;

    void setDistanceForDay(std::size_t day, Distance distance);
    const MaintenanceLog& getMaintenanceLog() const;
    const ControlStation* getStation() const;
    void print() const;
    static std::size_t getObjectCount();
    static const std::string& getClassName();
};

template <typename Charge, typename Distance>
std::ostream& operator<<(std::ostream& output, const QuadrupedRobot<Charge, Distance>& robot);

#include "robot_impl.hpp"
#include "robot_access_impl.hpp"
