#pragma once
#include "ClientDataBase.h"
#include "Logger.h"

#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
using namespace std;
class Authenticator
{
private:
    ClientDataBase db;
    Logger& logger;

public:
    Authenticator(const std::string& db_filename, Logger& logger);
    bool isLoginExists(const std::string& login);
    std::string generateSalt();
    bool verifyPassword(const std::string& login, const std::string& password, const std::string& salt);
    string generateSALT();
    string hashPassword(const string& salt_16, const string& password);
    bool compareHashes(const std::string& clientHash, const std::string& salt, const std::string& login);
};