#pragma once

#include <fstream>
#include <mutex>
#include <string>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <cstring> 
#include <cerrno>


enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
   // Logger();
    Logger(const std::string& filename);
    void open();
    void close();
    ~Logger();
    void log(LogLevel level, const std::string& message);
    void setLogFile(const std::string& filename);
    std::string getLogFile() const;
    bool GetIsOpen() const;
private:
    std::string filename;
    bool is_open;
    void handleError(const std::string& error_message);
    std::string currentDateTime();
    std::string logLevelToString(LogLevel level);
    std::ofstream log_file;
    std::mutex mutex_;
};
