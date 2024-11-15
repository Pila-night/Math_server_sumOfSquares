#pragma once

#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include "Logger.h"
#include "server.h"
namespace po = boost::program_options;


struct Params {
    std::string dataFileName;
    std::string logFileName;
    int port;
};

class Interface {
public:
    Interface();
    bool Parser(int argc, const char** argv);
    void processCommands(int argc, const char** argv);
    const Params& getParams() const; 
    Logger& getLogger();
    int getPort() const; 
    const std::string& getClientDataFile() const;
    string getDescription();
private:
    Params params; 
    Logger logger;
    po::options_description desc;
    po::variables_map vm;

};
