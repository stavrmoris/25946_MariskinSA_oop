#pragma once

#include <string>

namespace ordinary {
class QuadrupedRobot {
private:
    std::string name_;

public:
    explicit QuadrupedRobot(const std::string& name);
    virtual ~QuadrupedRobot();
    const std::string& getName() const;
};

class CargoRobot : public QuadrupedRobot {
private:
    double cargo_weight_;

public:
    CargoRobot(const std::string& name, double cargo_weight);
    ~CargoRobot() override;
    double getCargoWeight() const;
};

class AutonomousRobot : public QuadrupedRobot {
private:
    double autonomous_range_;

public:
    AutonomousRobot(const std::string& name, double autonomous_range);
    ~AutonomousRobot() override;
    double getAutonomousRange() const;
};

class AutonomousCargoRobot : public CargoRobot, public AutonomousRobot {
public:
    AutonomousCargoRobot(const std::string& name, double cargo_weight, double autonomous_range);
    ~AutonomousCargoRobot() override;
};
}

namespace fixed {
class QuadrupedRobot {
private:
    std::string name_;

public:
    explicit QuadrupedRobot(const std::string& name);
    virtual ~QuadrupedRobot();
    const std::string& getName() const;
};

class CargoRobot : public virtual QuadrupedRobot {
private:
    double cargo_weight_;

public:
    CargoRobot(const std::string& name, double cargo_weight);
    ~CargoRobot() override;
    double getCargoWeight() const;
};

class AutonomousRobot : public virtual QuadrupedRobot {
private:
    double autonomous_range_;

public:
    AutonomousRobot(const std::string& name, double autonomous_range);
    ~AutonomousRobot() override;
    double getAutonomousRange() const;
};

class AutonomousCargoRobot : public CargoRobot, public AutonomousRobot {
public:
    AutonomousCargoRobot(const std::string& name, double cargo_weight, double autonomous_range);
    ~AutonomousCargoRobot() override;
};
}
