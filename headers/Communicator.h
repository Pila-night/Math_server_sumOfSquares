
#pragma once
#include "Logger.h"

#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>

class Communicator
{

private:
    std::string dataFile;
    Logger& logger;
    std::vector<int32_t> readVector();
    int client_socket;
    void sendResponse(const std::string& response);
    bool isValidInt32Vector(const std::vector<int32_t>& vectorValues);
public:
    Communicator(int client_socket, const std::string& dataFile, Logger& logger);

    void handleClient();
    ~Communicator();
    void processVectors();
    void sendResultToClient(int32_t resultValue);
};
