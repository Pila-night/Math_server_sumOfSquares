#include "ClientDataBase.h"
#include "Logger.h"
using namespace std;
ClientDataBase::ClientDataBase(const string& filename)
{
    loadDatabase(filename);
}

bool ClientDataBase::isLoginExists(const string& login)
{
    return database.find(login) != database.end();                   
}

void ClientDataBase::loadDatabase(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line, ':')) {
            string login = line;
            string password;
            getline(file, password); 
            password.erase(password.find_last_not_of(" \t\r\n") + 1);
            database[login] = password; 
        }

        file.close();
    } else {
         cerr << "Ошибка: Не удалось открыть файл " << filename << endl;
         std::string error_message = strerror(errno);
         std::string exception_message = "Критическая ошибка: Не удалось открыть файл " + filename + " " + error_message;
         throw std::system_error(errno, std::generic_category(), exception_message);
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
