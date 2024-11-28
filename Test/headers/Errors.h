#pragma once
#include <stdexcept>
#include <string>

class DatabaseException : public std::invalid_argument {
public:
    explicit DatabaseException(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}

    explicit DatabaseException(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};



class CommunicatorException : public std::runtime_error {
public:
    explicit CommunicatorException(const std::string& message)
        : std::runtime_error(message) {}
};
