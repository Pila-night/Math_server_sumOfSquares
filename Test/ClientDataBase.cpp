#include "ClientDataBase.h"
#include "Logger.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

using namespace std;

ClientDataBase::ClientDataBase(const std::string& filename, Logger& log, bool one_start) {
    loadDatabase(filename, log, one_start);
}

bool ClientDataBase::isLoginExists(const string& login) const{
    return database.find(login) != database.end();                   
}

void ClientDataBase::loadDatabase(const std::string& filename, Logger& logger, bool one_start) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw CriticalDatabaseException("Error opening file: " + filename);
    }

    std::string line;
    this->database.clear(); 
    bool hasValidPair = false; 

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) {
            continue; 
        }

        size_t delimiterPos = line.find(':');
        if (delimiterPos == std::string::npos) {
            continue; 
        }

        std::string login = line.substr(0, delimiterPos);
        std::string password = line.substr(delimiterPos + 1);
        
        login.erase(0, login.find_first_not_of(" \t\r\n"));
        login.erase(login.find_last_not_of(" \t\r\n") + 1);
        password.erase(0, password.find_first_not_of(" \t\r\n"));
        password.erase(password.find_last_not_of(" \t\r\n") + 1);

        if (login.empty() || password.empty()) {
          	if(one_start == true){
            logger.log(WARNING, "Обнаружена пара с пустым логином или паролем в строчке: " + line);
            }
            continue; 
        }

        this->database[login] = password;
        hasValidPair = true; 
    }
    file.close();
    if (!hasValidPair) {        throw CriticalDatabaseException("Не найдено ни одной валидной пары логин:пароль");
    }
}

std::string& ClientDataBase::operator[](const std::string& login) {
    return database[login]; 
}

const std::string& ClientDataBase::operator[](const std::string& login) const {
    return database.at(login); 
}

