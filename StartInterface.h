/**
 * @file StartInterface.h
 * @brief Заголовочный файл класса Interface для обработки параметров командной строки.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include "Logger.h"
#include "server.h"
namespace po = boost::program_options;


/**
 * @struct Params
 * @brief Структура для хранения параметров, полученных из командной строки.
 */
struct Params {
    std::string dataFileName;  ///< Имя файла с данными клиентов.
    std::string logFileName;   ///< Имя файла журнала событий.
    int port;                  ///< Порт сервера.
};

/**
 * @class Interface
 * @brief Класс для обработки параметров командной строки и инициализации сервера.
 *
 *  Использует библиотеку Boost.Program_options для парсинга аргументов командной строки.
 */
class Interface {
public:
    /**
     * @brief Конструктор класса Interface.
     *  Инициализирует параметры по умолчанию.
     */
    Interface();
    /**
     * @brief Парсит параметры командной строки.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @return true, если параметры успешно спарсены, false в противном случае (например, если был передан ключ --help).
     */
    bool Parser(int argc, const char** argv);
    /**
     * @brief Обрабатывает параметры командной строки, инициализирует логгер и проверяет корректность параметров.
     * @param argc Количество аргументов.
     * @param argv Массив аргументов.
     * @throw std::runtime_error При некорректном порте или отсутствии файла с данными клиентов.
     */
    void processCommands(int argc, const char** argv);
    /**
     * @brief Возвращает константную ссылку на структуру параметров.
     * @return Константная ссылка на структуру Params.
     */
    const Params& getParams() const; 
    /**
     * @brief Возвращает ссылку на объект Logger.
     * @return Ссылка на объект Logger.
     */
    Logger& getLogger();
    /**
     * @brief Возвращает номер порта.
     * @return Номер порта.
     */
    int getPort() const; 
    /**
     * @brief Возвращает имя файла с данными клиентов.
     * @return Имя файла с данными клиентов.
     */
    const std::string& getClientDataFile() const;
    /**
     * @brief Возвращает строковое описание параметров командной строки.
     * @return Строка с описанием параметров.
     */
    string getDescription();
private:
    Params params;          ///< Структура для хранения параметров
    Logger logger;          ///< Объект для логирования
    po::options_description desc; ///< Описание параметров командной строки
    po::variables_map vm;   ///< Хранилище для распарсенных параметров
};
