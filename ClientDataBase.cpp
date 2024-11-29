/**
 * @file ClientDataBase.cpp
 * @brief Реализация класса ClientDataBase
 */
#include "ClientDataBase.h"
#include "Logger.h"
#include <sstream>

using namespace std;
ClientDataBase::ClientDataBase(const string& filename)
{
    loadDatabase(filename);
}

bool ClientDataBase::isLoginExists(const string& login)
{
    return database.find(login) != database.end();                   
}

void ClientDataBase::loadDatabase(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw CriticalDatabaseException("Error opening file: " + filename);
    }

    std::string line;
    int validLines = 0;
    this->database.clear(); 

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
            continue; 
        }
        
        if (this->database.count(login)) {
            continue; 
        }

        this->database[login] = password;
        validLines++;
    }
    
    file.close();
    
    if (validLines == 0) {
        throw CriticalDatabaseException("Critical Error: No valid login-password pairs found in the database file.");
    }
}

std::string& ClientDataBase::operator[](const std::string& login)
{
    return database[login]; 
}

const std::string& ClientDataBase::operator[](const std::string& login) const 
{
    return database.at(login); 
}
