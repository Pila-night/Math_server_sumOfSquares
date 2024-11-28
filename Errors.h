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
class DatabaseException : public std::invalid_argument {
public:
    /**
     * @brief Конструктор DatabaseException.
     * @param what_arg Текстовое сообщение, описывающее ошибку.
     */
    explicit DatabaseException(const std::string& what_arg)
        : std::invalid_argument(what_arg) {}

    /**
     * @brief Конструктор DatabaseException.
     * @param what_arg Текстовое сообщение, описывающее ошибку.
     */
    explicit DatabaseException(const char* what_arg)
        : std::invalid_argument(what_arg) {}
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
