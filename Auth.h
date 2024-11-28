/**
 * @file Auth.h
 * @brief Файл содержит класс Authenticator для аутентификации пользователей.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include "ClientDataBase.h"
#include "Logger.h"

#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
using namespace std;

namespace CPP = CryptoPP;

/**
 * @class Authenticator
 * @brief Обрабатывает аутентификацию пользователей по базе данных.
 */
class Authenticator {
private:
    ClientDataBase db;  ///< База данных для хранения учетных данных пользователей.
    Logger& logger;     ///< Объект логгера для записи событий аутентификации.

public:
    /**
     * @brief Конструктор объекта Authenticator.
     * 
     * @param db_filename Путь к файлу базы данных.
     * @param logger Ссылка на объект логгера.
     */
    Authenticator(const std::string& db_filename, Logger& logger);

    /**
     * @brief Проверяет, существует ли логин в базе данных.
     * 
     * @param login Логин пользователя для проверки.
     * @return True, если логин существует, иначе false.
     */
    bool isLoginExists(const std::string& login);

    /**
     * @brief Генерирует случайную соль длиной 16 символов в шестнадцатеричном формате.
     * 
     * @return Сгенерированная соль.
     */
    std::string generateSalt();

    /**
     * @brief Хэширует пароль с использованием SHA224 и заданной солью.
     * 
     * @param salt_16 Соль длиной 16 символов в шестнадцатеричном формате.
     * @param password Пароль для хэширования.
     * @return Хэш SHA224 пароля, конкатенированного с солью.
     */
    std::string hashPassword(const std::string& salt_16, const std::string& password);

    /**
     * @brief Сравнивает полученный от клиента хэш с сгенерированным на сервере.
     * 
     * @param clientHash Хэш, полученный от клиента.
     * @param salt Соль, использованная для хэширования.
     * @param login Логин пользователя.
     * @return True, если хэши совпадают, иначе false.
     */
    bool compareHashes(const std::string& clientHash, const std::string& salt, const std::string& login);

    /**
     * @brief Проверяет пароль пользователя в базе данных.
     * @param login Логин пользователя.
     * @param password Пароль пользователя.
     * @param salt Соль, связанная с паролем пользователя.
     * @return True, если пароль валиден, иначе false.
     */
    bool verifyPassword(const std::string& login, const std::string& password, const std::string& salt);
};
