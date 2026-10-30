#include "control_station.h"

#include <iostream>
#include <stdexcept>

ControlStation::ControlStation(const std::string& name) : name_(name)
{
    if (name_.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("имя станции не должно быть пустым");
    }
    std::cout << "[станция] создана: " << name_ << '\n';
}

ControlStation::~ControlStation()
{
    std::cout << "[станция] уничтожена: " << name_ << '\n';
}

const std::string& ControlStation::getName() const { return name_; }

void ControlStation::setName(const std::string& name)
{
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("имя станции не должно быть пустым");
    }
    name_ = name;
}
