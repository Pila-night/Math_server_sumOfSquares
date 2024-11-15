#pragma once
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
class ClientDataBase
{
private:
    void loadDatabase(const std::string& filename);
    std::unordered_map<std::string, std::string> database;
    //Logger& logger;
public:
    ClientDataBase(const std::string& filename);
    bool isLoginExists(const std::string& login);
    std::string& operator[](const std::string& login);
    const std::string& operator[](const std::string& login) const;
};
