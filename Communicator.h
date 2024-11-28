/**
 * @file Communicator.h
 * @brief Этот файл содержит определение класса Communicator, отвечающего за коммуникацию с клиентами.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include "Logger.h"

#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <vector>

/**
 * @class Communicator
 * @brief Этот класс отвечает за обработку коммуникации с клиентом.  Он принимает векторы данных от клиента, обрабатывает их и отправляет результат обратно.
 */
class Communicator {

private:
    std::string dataFile;          ///< Путь к файлу данных, используемому в процессе обработки (если требуется).
    Logger& logger;                 ///< Ссылка на объект Logger для ведения логов.
    int client_socket;             ///< Дескриптор сокета, используемого для общения с клиентом.

    /**
     * @brief Отправляет ответ клиенту через сокет.
     * @param response Строка, содержащая ответ, который нужно отправить клиенту.
     */
    void sendResponse(const std::string& response);


public:
    /**
     * @brief Конструктор класса Communicator. Инициализирует объект, устанавливая связь с клиентом и настраивая логирование.
     * @param client_socket Дескриптор сокета, через который происходит общение с клиентом.
     * @param dataFile Путь к файлу данных (если используется).
     * @param logger Ссылка на объект Logger для записи логов.
     */
    Communicator(int client_socket, const std::string& dataFile, Logger& logger);

    /**
     * @brief Основной метод обработки запроса клиента.  Принимает данные от клиента, обрабатывает их и отправляет ответ.
     */
    void handleClient();

    /**
     * @brief Деструктор класса Communicator. Закрывает сокет после завершения работы.
     */
    ~Communicator();

    /**
     * @brief Обрабатывает полученные от клиента векторы данных.  
     */
    void processVectors();

    /**
     * @brief Отправляет результат обработки векторов клиенту.
     * @param resultValue Значение результата, которое нужно отправить клиенту.  Тип int32_t.
     */
    void sendResultToClient(int32_t resultValue);
};
