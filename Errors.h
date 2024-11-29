/**
 * @file Errors.h
 * @brief Этот файл содержит определение класса Communicator, отвечающего за коммуникацию с клиентами.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include <stdexcept>
#include <string>

/**
 * @class DatabaseException
 * @brief Исключение, возникающее при ошибках работы с базой данных.
 */
// Базовый класс для всех исключений базы данных
class DatabaseException : public std::invalid_argument {
public:
    explicit DatabaseException(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}

    explicit DatabaseException(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

// Класс для некритических исключений
class NonCriticalDatabaseException : public DatabaseException {
public:
    explicit NonCriticalDatabaseException(const std::string& what_arg)
        : DatabaseException(what_arg) {}

    explicit NonCriticalDatabaseException(const char* what_arg)
        : DatabaseException(what_arg) {}
};

// Класс для критических исключений
class CriticalDatabaseException : public DatabaseException {
public:
    explicit CriticalDatabaseException(const std::string& what_arg)
        : DatabaseException(what_arg) {}

    explicit CriticalDatabaseException(const char* what_arg)
        : DatabaseException(what_arg) {}
};

// Класс для предупреждений
class WarningDatabaseException : public DatabaseException {
public:
    explicit WarningDatabaseException(const std::string& what_arg)
        : DatabaseException(what_arg) {}

    explicit WarningDatabaseException(const char* what_arg)
        : DatabaseException(what_arg) {}
};

/**
 * @class CommunicatorException
 * @brief Исключение, возникающее при ошибках в процессе коммуникации.
 */
class CommunicatorException : public std::runtime_error {
public:
    /**
     * @brief Конструктор CommunicatorException.
     * @param message Текстовое сообщение, описывающее ошибку.
     */
    explicit CommunicatorException(const std::string& message)
        : std::runtime_error(message) {}
};
