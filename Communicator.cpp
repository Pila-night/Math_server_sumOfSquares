
#include "Auth.h"
#include "ClientDataBase.h"
#include "Communicator.h"
#include "HandlerVector.h"

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

Communicator::Communicator(int socket, const std::string& dataFile, Logger& logger)
    : dataFile(dataFile)
    , logger(logger)
    , client_socket(socket)
{
}

void Communicator::handleClient()
{
    char login[1024] = { 0 };
    ssize_t recvlogin = recv(client_socket, login, sizeof(login), 0);
    if(recvlogin == 0) {

        std::string error_message = strerror(errno);
        std::string exception_message = "Клиент закрыл соединение: " + error_message;
        logger.log(ERROR, exception_message);
    } else if(recvlogin < 0) {
        std::string error_message = strerror(errno);
        std::string exception_message = "Ошибка получения логина: " + error_message;
        throw std::system_error(errno, std::generic_category(), exception_message);
    }
    for(ssize_t i = 0; i < recvlogin; ++i) {
        if(login[i] == '\n') {
            login[i] = '\0';
            break;
        }
    }
    logger.log(INFO, "Клиент прислал логин: " + string(login));
    Authenticator authenticator(dataFile, logger);
    if(authenticator.isLoginExists(login) == false) {
        logger.log(ERROR, "Клиент не прошел аутентификацию");
        const string errMsg = "ERR";
        send(client_socket, errMsg.c_str(), errMsg.size(), 0);
        close(client_socket);
    } else {
        string salt = authenticator.generateSALT();
        send(client_socket, salt.c_str(), salt.size(), 0);
        logger.log(INFO, "Клиенту отправлена соль: " + salt);
        char clientHash[1024] = { 0 };
        ssize_t recvlclientHash = recv(client_socket, clientHash, sizeof(clientHash), 0);
        if(recvlogin == 0) {
            std::string error_message = strerror(errno);
            std::string exception_message = "Клиент закрыл соединение: " + error_message;
            logger.log(ERROR, exception_message);
        } else if(recvlogin < 0) {
            std::string error_message = strerror(errno);
            std::string exception_message = "Ошибка получения хеша: " + error_message;
            throw std::system_error(errno, std::generic_category(), exception_message);
        }
        for(ssize_t i = 0; i < recvlclientHash; ++i) {
            if(clientHash[i] == '\n') {
                clientHash[i] = '\0';
                break;
            }
        }
        if(authenticator.compareHashes(clientHash, salt, login)) {
            logger.log(INFO, "Клиент прошел аутентификацию");
            const string successMsg = "OK\n";
            send(client_socket, successMsg.c_str(), successMsg.size(), 0);
            processVectors();
        } else {
            logger.log(ERROR, "Клиент не прошел аутентификацию");
            const string errMsg = "ERR\n";
            send(client_socket, errMsg.c_str(), errMsg.size(), 0);
        }
    }
}

void Communicator::processVectors()
{
    logger.log(INFO, "Начинаю обработку векторов");
    uint32_t numVectors = 0;
    ssize_t recvBytes = recv(client_socket, &numVectors, sizeof(numVectors), 0);

    if(recvBytes != sizeof(numVectors)) {
        std::string error_message = strerror(errno);
        std::string exception_message = "Ошибка получения количества векторов : " + error_message;
        logger.log(ERROR, exception_message);
        close(client_socket);
    } else {

        logger.log(INFO, "От клиента пришло " + to_string(numVectors) + " векторов");

        for(uint32_t i = 0; i < numVectors; ++i) {
            std::vector<int32_t> vectorValues;
            readVector(vectorValues);
            int32_t resultValue = HandlerVector::processVector(vectorValues);
            logger.log(INFO, "Результат вычисления по  " + to_string(i + 1) + " вектору: " + to_string(resultValue));
            sendResultToClient(resultValue);
        }
    }
}

void Communicator::readVector(std::vector<int32_t>& vectorValues)
{

    uint32_t vectorSize = 0;
    ssize_t recvBytes = recv(client_socket, &vectorSize, sizeof(vectorSize), 0);

    if(recvBytes != sizeof(vectorSize)) {
        std::string error_message = strerror(errno);
        std::string exception_message = "Ошибка получения размера вектора: " + error_message;
        logger.log(ERROR, exception_message);
    } else {

        vectorValues.resize(vectorSize);

        size_t bytesRead = 0;
        while(bytesRead < vectorSize * sizeof(int32_t)) {
            recvBytes = recv(client_socket, reinterpret_cast<char*>(vectorValues.data()) + bytesRead,
                             vectorSize * sizeof(int32_t) - bytesRead, 0);

            if(recvBytes <= 0) {
                std::string error_message = strerror(errno);
                std::string exception_message = "Ошибка чтения из сокета: " + error_message;
                logger.log(CRITICAL, exception_message);
            }

            bytesRead += recvBytes;
        }
    }
}

void Communicator::sendResultToClient(int32_t resultValue)
{
    ssize_t sentBytes = send(client_socket, &resultValue, sizeof(resultValue), 0);
    logger.log(INFO, "Отправил клиенту результаты вычислений");
    if(sentBytes != sizeof(resultValue)) {
        std::string error_message = strerror(errno);
        std::string exception_message = "Ошибка чтения из сокета: " + error_message;
        logger.log(ERROR, exception_message);
    }
}
Communicator::~Communicator() { close(client_socket); }
