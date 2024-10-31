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

class Server
{
private:
    int port;
    std::string data;
    Logger& logger;
    int server_socket;
    void handleClient(int client_socket);
    void listen_socket();

public:
    Server(int port, const std::string& data, Logger& logger);
    Server() = delete;
    ~Server() {}
    void start();
};