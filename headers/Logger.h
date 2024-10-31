#pragma once

#include <fstream>
#include <mutex>
#include <string>
#include <ctime>
#include <iostream>
#include <stdexcept>

enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();
    void log(LogLevel level, const std::string& message);

private:
    void handleError(const std::string& error_message);
    std::string currentDateTime();
    std::string logLevelToString(LogLevel level);
    std::ofstream log_file;
    std::mutex mutex_;
};