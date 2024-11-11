#include "Logger.h"

Logger::Logger(const std::string& filename) : filename(filename), is_open(false) {}
void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    this->filename = filename; 
}

Logger::~Logger() {
        close(); 
    }

void Logger::open() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!is_open) {
        log_file.open(filename, std::ios::app);
        if (!log_file.is_open()) {
            std::string error_message = "Не удалось получить доступ к " + filename + ": " + strerror(errno) + 
                                         ". В директории запуска сервера создан файл с логами: vcalc.log";
            std::cout <<error_message << std::endl;
            log_file.open("vcalc.log", std::ios::app);
            if (!log_file.is_open()) {
                handleError("Не удалось открыть файл журнала: vcalc.log");
            } else {
                is_open = true;
                this->filename = "vcalc.log"; 
            }
        } else {
            is_open = true;
        }
    }
}


void Logger::close() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (is_open) {
            log_file.close();
            is_open = false;
        }
    }

void Logger::log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!is_open) {
            handleError("Файл журнала закрыт: " + filename);
            return;
        }

        log_file << currentDateTime() << " [" << logLevelToString(level) << "] " << message << std::endl;
        std::cout << currentDateTime() << " [" << logLevelToString(level) << "] " << message << std::endl;

        if (level == CRITICAL) {
            handleError("Критическая ошибка: " + message);
        }
    }

void Logger::handleError(const std::string& error_message) {
    std::cerr << error_message << std::endl;
    throw std::runtime_error(error_message);
}

std::string Logger::currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    localtime_r(&now, &tstruct);

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}


std::string Logger::getLogFile() const {
    return filename;
}

