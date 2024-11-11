#pragma once

#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include "Logger.h"
#include "server.h"

class Interface {
public:
    Interface();
    void processCommands(int argc, const char** argv);
    int getPort() const;
    const std::string& getClientDataFile() const;
    Logger& getLogger();

private:
    int port;
    std::string clientDataFile;
    Logger logger; 
};
