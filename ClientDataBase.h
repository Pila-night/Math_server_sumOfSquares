#pragma once
/**
 * @file ClientDataBase.h
 * @brief Заголовочный файл класса ClientDataBase, реализующего работу с базой данных клиентов.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "Errors.h"

/**
 * @class ClientDataBase
 * @brief Класс для работы с базой данных клиентов, хранящей логины и пароли.
 *
 * База данных загружается из файла при создании объекта. Обеспечивает проверку существования логина и доступ к паролю по логину.
 *  @warning Файл должен содержать данные в формате "логин:пароль".
 */
class ClientDataBase
{
private:
    /**
     * @brief Загружает базу данных из файла.
     * @param filename Имя файла базы данных.
     * @param logger Объект логгера для вывода сообщений.
     * @param on_start Флаг, указывающий на первый запуск приложения.
     */
    void loadDatabase(const std::string& filename, Logger& logger, bool one_start);

    std::unordered_map<std::string, std::string> database;

public:
    /**
     * @brief Конструктор класса ClientDataBase.
     * @param filename Путь к файлу базы данных.
     * @param log Объект логгера для вывода сообщений.
     * @param on_start Флаг, указывающий на первый запуск приложения.
     */
    ClientDataBase(const std::string& filename, Logger& log, bool one_start);

    /**
     * @brief Проверяет существование логина в базе данных.
     * @param login Логин для проверки.
     * @return true, если логин существует, false в противном случае.
     */
    bool isLoginExists(const std::string& login) const;

    /**
     * @brief Возвращает ссылку на пароль по заданному логину.
     * @param login Логин.
     * @return Ссылка на строку, содержащую пароль.
     */
    std::string& operator[](const std::string& login);

    /**
     * @brief Возвращает константную ссылку на пароль по заданному логину.
     * @param login Логин.
     * @return Константная ссылка на строку, содержащую пароль.
     */
    const std::string& operator[](const std::string& login) const;
};
