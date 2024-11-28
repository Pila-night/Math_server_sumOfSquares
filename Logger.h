/**
 * @file Logger.h
 * @brief Заголовочный файл класса Logger для ведения логов.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include <fstream>
#include <mutex>
#include <string>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <cstring> 

/**
 * @enum LogLevel
 * @brief Уровни логирования.
 */
enum LogLevel {
    INFO,    ///< Информационное сообщение
    WARNING, ///< Предупреждение
    ERROR,   ///< Ошибка
    CRITICAL ///< Критическая ошибка
};

/**
 * @class Logger
 * @brief Класс для ведения логов в файл.
 * 
 *  Обеспечивает потокобезопасное логирование с возможностью указать файл для логов и несколькими уровнями серьезности сообщений.
 *  При невозможности записи в указанный файл, пытается создать файл "vcalc.log" в директории запуска.
 */
class Logger {
public:
    /**
     * @brief Конструктор класса Logger.
     * @param filename Имя файла для логирования.
     * @throw std::invalid_argument Если filename пустой.
     */
    Logger(const std::string& filename);
    /**
     * @brief Открывает файл для записи логов.
     *  Если файл не может быть открыт, выводится сообщение об ошибке и создается файл "vcalc.log".
     */
    void open();
    /**
     * @brief Закрывает файл для записи логов.
     */
    void close();
    /**
     * @brief Деструктор класса Logger. Закрывает файл логов.
     */
    ~Logger();
    /**
     * @brief Записывает сообщение в лог-файл.
     * @param level Уровень серьезности сообщения.
     * @param message Текст сообщения.
     */
    void log(LogLevel level, const std::string& message);
    /**
     * @brief Устанавливает новое имя файла для логирования.
     * @param filename Новое имя файла.
     * @throw std::invalid_argument Если filename пустой.
     */
    void setLogFile(const std::string& filename);
    /**
     * @brief Возвращает текущее имя файла для логирования.
     * @return Текущее имя файла.
     */
    std::string getLogFile() const;
    /**
     * @brief Проверяет открыт ли файл для логирования.
     * @return true если файл открыт, false иначе.
     */
    bool GetIsOpen() const;
private:
    std::string filename;      ///< Имя файла для логирования
    bool is_open;              ///< Флаг, указывающий открыт ли файл
    /**
     * @brief Обрабатывает ошибку, выводя сообщение на стандартный поток ошибок и выбрасывая исключение.
     * @param error_message Текст сообщения об ошибке.
     */
    void handleError(const std::string& error_message);
    /**
     * @brief Возвращает текущую дату и время в формате YYYY-MM-DD HH:MM:SS.
     * @return Текущая дата и время в формате строки.
     */
    std::string currentDateTime();
    /**
     * @brief Преобразует уровень логирования в строковое представление.
     * @param level Уровень логирования.
     * @return Строковое представление уровня логирования.
     */
    std::string logLevelToString(LogLevel level);
    std::ofstream log_file;    ///< Поток для записи в файл
    std::mutex mutex_;         ///< Мьютекс для обеспечения потокобезопасности
};
