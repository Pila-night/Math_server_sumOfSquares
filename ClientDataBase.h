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

/**
 * @class ClientDataBase
 * @brief Класс для работы с базой данных клиентов, хранящей логины и пароли.
 * 
 *  База данных загружается из файла при создании объекта.  Обеспечивает проверку существования логина и доступ к паролю по логину.
 */
class ClientDataBase
{
private:
    /**
     * @brief Загружает данные из файла в базу данных.
     * @param filename Имя файла базы данных.
     * @throw DatabaseException Если в файле обнаружен логин или пароль без пары.
     * @throw std::runtime_error Если база данных пуста после загрузки.
     * @throw std::system_error Если не удалось открыть файл.
     */
    void loadDatabase(const std::string& filename);
    /**
     * @brief Внутренняя база данных, хранящая пары логин-пароль.
     */
    std::unordered_map<std::string, std::string> database;
public:
    /**
     * @brief Конструктор класса ClientDataBase.
     * @param filename Имя файла базы данных.
     * @throw DatabaseException Если в файле обнаружен логин или пароль без пары.
     * @throw std::runtime_error Если база данных пуста после загрузки.
     * @throw std::system_error Если не удалось открыть файл.
     */
    ClientDataBase(const std::string& filename);
    /**
     * @brief Проверяет существование логина в базе данных.
     * @param login Проверяемый логин.
     * @return true, если логин существует, false в противном случае.
     */
    bool isLoginExists(const std::string& login);
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
