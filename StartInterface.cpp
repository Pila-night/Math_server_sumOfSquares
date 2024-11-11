#include "StartInterface.h"
#include <iostream>
#include <fstream>

namespace po = boost::program_options;

Interface::Interface() : port(33333),   logger("") { 
}

void Interface::processCommands(int argc, const char** argv) { 
    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "Вывести справку")
        ("data,d", po::value<std::string>()->default_value("/etc/vcalc.conf"),
         "Имя файла с базой клиентов (необходимо запускать от имени администратора для доступа к этому файлу)")
        ("log,l", po::value<std::string>()->default_value("/var/log/vcalc.log"),
         "Имя файла с журналом работы (необходимо запускать от имени администратора для записи в этот файл)")
        ("port,p", po::value<int>()->default_value(33333), "Номер порта для прослушки");

    po::variables_map vm;
    if (argc == 1) {
        std::cout << desc << std::endl;
        exit(1);
    }
    
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(1);
    }

    clientDataFile = vm["data"].as<std::string>();
    std::string logFile = vm["log"].as<std::string>();
    port = vm["port"].as<int>();

 
    logger.setLogFile(logFile);
    logger.open(); 

    std::ifstream clientData(clientDataFile);
    if (!clientData.is_open()) {
        std::string error_message = "Файл с базой клиентов " + clientDataFile + " не найден.";
        logger.log(CRITICAL, error_message); 
    }
    
    if (clientData.peek() == std::ifstream::traits_type::eof()) {
    std::string error_message = "Файл с базой клиентов " + clientDataFile + " пустой.";
    logger.log(CRITICAL, error_message);
    }
    logger.log(INFO, "Файл с базой клиентов: " + clientDataFile);
    logger.log(INFO, "Файл с журналом работы: " + logger.getLogFile());
    logger.log(INFO, "Порт: " + std::to_string(port));
}

int Interface::getPort() const { return port; }
const std::string& Interface::getClientDataFile() const { return clientDataFile; }
Logger& Interface::getLogger() { return logger; }
