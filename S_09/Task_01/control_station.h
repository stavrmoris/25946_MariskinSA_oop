#pragma once

#include <string>

class ControlStation {
private:
    std::string name_;

public:
    explicit ControlStation(const std::string& name);
    ~ControlStation();
    const std::string& getName() const;
    void setName(const std::string& name);
};
