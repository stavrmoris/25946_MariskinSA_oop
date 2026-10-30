#pragma once

#include <iosfwd>
#include <string>

class ControlStation;

template <typename Charge, typename Distance>
class QuadrupedRobot;

template <typename Charge, typename Distance>
void renameRobot(QuadrupedRobot<Charge, Distance>& robot, const std::string& name);

class RobotTechnician {
public:
    template <typename Charge, typename Distance>
    void recharge(QuadrupedRobot<Charge, Distance>& robot, Charge battery) const;

    template <typename Charge, typename Distance>
    void resetToday(QuadrupedRobot<Charge, Distance>& robot) const;

    template <typename Charge, typename Distance>
    void addServiceEntry(QuadrupedRobot<Charge, Distance>& robot, const std::string& text) const;

    template <typename Charge, typename Distance>
    void connect(QuadrupedRobot<Charge, Distance>& robot, ControlStation& station) const;

    template <typename Charge, typename Distance>
    void disconnect(QuadrupedRobot<Charge, Distance>& robot) const;
};

class RobotInspector {
public:
    template <typename Charge, typename Distance>
    void clearHistory(QuadrupedRobot<Charge, Distance>& robot) const;

    template <typename Charge, typename Distance>
    void describe(const QuadrupedRobot<Charge, Distance>& robot, std::ostream& output) const;
};
