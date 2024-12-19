/**
 * @file StartInterface.cpp
 * @brief Реализация класса Interface для обработки параметров командной строки.
 */
#include "StartInterface.h"
#include "ClientDataBase.h"
#include <sstream>
#include <iostream>
#include <fstream>

namespace po = boost::program_options;

Interface::Interface(int argc, const char** argv) : logger("/var/log/vcalc.log") {
    params.dataFileName = "/etc/vcalc.conf"; 
    params.logFileName = "/var/log/vcalc.log"; 
    params.port = 33333; 

    desc.add_options()
        ("help,h", "Получить справку")
        ("data,d", po::value<std::string>(&params.dataFileName)->default_value("/etc/vcalc.conf"), "Файл с базой данных")
        ("log,l", po::value<std::string>(&params.logFileName)->default_value("/var/log/vcalc.log"), "Журнал событий")
        ("port,p", po::value<int>(&params.port)->default_value(33333), "Порт");
    processCommands(argc, argv);
}

bool Interface::Parser(int argc, const char** argv) {
    po::store(po::parse_command_line(argc, argv, desc), vm);
     if (argc == 1) {
        std::cout << desc << std::endl;
    }
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return false;
    }
    
    po::notify(vm);
    return true;
}

void Interface::processCommands(int argc, const char** argv) {
    if (!Parser(argc, argv)) {
        exit(1);
    }

    logger.setLogFile(params.logFileName);
    logger.open();

    if (params.port < 1 || params.port > 65535) {
        std::string error_message = "Неверный порт: " + std::to_string(params.port) + ". Порт должен быть в диапазоне от 1 до 65535";
        logger.log(CRITICAL, error_message);
        throw std::runtime_error(error_message);
    }

    std::ifstream clientData(params.dataFileName);
    if (!clientData.is_open()) {
        std::string error_message = "Файл с базой клиентов " + params.dataFileName + " не найден.";
        logger.log(CRITICAL, error_message);
    }

    if (clientData.peek() == std::ifstream::traits_type::eof()) {
        std::string error_message = "Файл с базой клиентов " + params.dataFileName + " пустой.";
        logger.log(CRITICAL, error_message);
    }
    
    logger.log(INFO, "Файл с базой клиентов: " + params.dataFileName);
    logger.log(INFO, "Файл с журналом работы: " + logger.getLogFile());
    logger.log(INFO, "Порт: " + std::to_string(params.port));
    try {
    ClientDataBase db(params.dataFileName, logger, true);
    }catch (const CriticalDatabaseException& e) {
        logger.log(CRITICAL, std::string("Критическая ошибка базы данных: ") + e.what());
    } catch (const std::exception& e) {
        logger.log(CRITICAL, std::string("Неизвестная ошибка: ") + e.what());
    }
    Server server(params.port,params.dataFileName, logger);
    server.start();
}

const Params& Interface::getParams() const { return params; } 

int Interface::getPort() const {
    return params.port; 
}

const std::string& Interface::getClientDataFile() const {
    return params.dataFileName; 
}

std::string Interface::getDescription() {
    std::ostringstream ss;
    ss << desc; 
    return ss.str();
}

Logger& Interface::getLogger() { return logger; }
