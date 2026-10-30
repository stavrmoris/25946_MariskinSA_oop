#include "maintenance_log.h"

#include <iostream>
#include <stdexcept>
#include <utility>

MaintenanceLog::MaintenanceLog() : entry_count_(0), last_entry_()
{
    std::cout << "[журнал] создан\n";
}

MaintenanceLog::MaintenanceLog(const MaintenanceLog& other)
    : entry_count_(other.entry_count_), last_entry_(other.last_entry_)
{
    std::cout << "[журнал] создана независимая копия\n";
}

MaintenanceLog::MaintenanceLog(MaintenanceLog&& other)
    : entry_count_(other.entry_count_), last_entry_(std::move(other.last_entry_))
{
    other.entry_count_ = 0;
    other.last_entry_.clear();
    std::cout << "[журнал] перемещён\n";
}

MaintenanceLog::~MaintenanceLog()
{
    std::cout << "[журнал] уничтожен\n";
}

void MaintenanceLog::addEntry(const std::string& text)
{
    if (text.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("запись обслуживания не должна быть пустой");
    }
    std::string entry(text);
    last_entry_.swap(entry);
    ++entry_count_;
}

void MaintenanceLog::swap(MaintenanceLog& other) noexcept
{
    std::swap(entry_count_, other.entry_count_);
    last_entry_.swap(other.last_entry_);
}

std::size_t MaintenanceLog::getEntryCount() const { return entry_count_; }
const std::string& MaintenanceLog::getLastEntry() const { return last_entry_; }
