/**
 * @file server.h
 * @brief Заголовочный файл класса Server.
 * @author Грачев В.В.
 * @version 1.0
 * @date 18.11.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include "Logger.h"

#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>
#include <vector>

using namespace std;

/**
 * @class Server
 * @brief Класс сетевого сервера.
 *
 *  Принимает соединения от клиентов, обрабатывает их и отправляет данные.
 *  Использует класс Logger для логирования событий.
 */
class Server
{
private:
    int port;             ///< Порт сервера
    std::string data;     ///< Данные для отправки клиентам
    Logger& logger;       ///< Объект для логирования
    int server_socket;    ///< Дескриптор серверного сокета
    /**
     * @brief Обрабатывает соединение с клиентом.
     * @param client_socket Дескриптор сокета клиента.
     */
    void handleClient(int client_socket);
    /**
     * @brief Начинает прослушивание сокета на наличие входящих соединений.
     */
    void listen_socket();
public:
    /**
     * @brief Конструктор класса Server.
     * @param port Порт сервера.
     * @param data Данные для отправки клиентам.
     * @param logger Объект для логирования.
     * @throw std::system_error При ошибках создания или привязки сокета.
     * @throw std::system_error При указании неверного номера порта.
     */
    Server(int port, const std::string& data, Logger& logger);
    Server() = delete;
    ~Server() {}
    /**
     * @brief Запускает сервер.
     *  В бесконечном цикле принимает соединения от клиентов и обрабатывает их.
     *  @throw std::system_error При ошибках приема соединения.
     */
    void start();
};
