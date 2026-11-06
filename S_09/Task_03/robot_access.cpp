#include "robot_access.h"

#include <stdexcept>

RobotFactory::RobotFactory(const std::string& name) : name_(name)
{
    const std::size_t first = name_.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        throw std::invalid_argument("название завода не должно быть пустым");
    }
    const std::size_t last = name_.find_last_not_of(" \t\r\n");
    name_ = name_.substr(first, last - first + 1);
}

const std::string& RobotFactory::getName() const { return name_; }
