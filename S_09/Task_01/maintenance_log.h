#pragma once

#include <cstddef>
#include <string>

class MaintenanceLog {
private:
    std::size_t entry_count_;
    std::string last_entry_;

public:
    MaintenanceLog();
    MaintenanceLog(const MaintenanceLog& other);
    MaintenanceLog(MaintenanceLog&& other);
    MaintenanceLog& operator=(const MaintenanceLog& other) = default;
    ~MaintenanceLog();

    void addEntry(const std::string& text);
    void swap(MaintenanceLog& other) noexcept;
    std::size_t getEntryCount() const;
    const std::string& getLastEntry() const;
};
