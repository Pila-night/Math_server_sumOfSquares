#include "Auth.h"
/**
 * @file Auth.cpp
 * @brief Файл содержит реализацию класса Authenticator для аутентификации пользователей.
 */
Authenticator::Authenticator(const std::string& db_filename, Logger& logger)
    : db(db_filename), logger(logger) 
{
}

bool Authenticator::isLoginExists(const std::string& login)
{
    return db.isLoginExists(login); 
}
string Authenticator::generateSalt()
{
    namespace CPP = CryptoPP;
    constexpr int salt_size = 8; // 64 бита = 8 байт
    CPP::byte salt[salt_size];
    CPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(salt, salt_size);
    std::string salt_16;
    CPP::ArraySource(salt, salt_size, true, new CPP::HexEncoder(new CPP::StringSink(salt_16)));

    //тут  дополняем слева нулями до 16 символов
    while(salt_16.length() < 16) {
        salt_16.insert(salt_16.begin(), '0');
    }
    return salt_16;
}

string Authenticator::hashPassword(const string& salt_16, const string& password)
{
    namespace CPP = CryptoPP;
    string HashAndPass = salt_16 + password; 
    CPP::SHA224 hash;                        
    CPP::byte digest[CryptoPP::SHA224::DIGESTSIZE];
    hash.CalculateDigest(digest, (const CPP::byte*)HashAndPass.data(), HashAndPass.size());
    string Hash;
    CryptoPP::StringSource(digest, sizeof(digest), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(Hash)));
    logger.log(INFO, "Сервер сгенерировал хэш: "+ Hash);
    return Hash;
}

bool Authenticator::compareHashes(const std::string& clientHash, const std::string& salt, const std::string& login)
{
    string password = db[login];
    logger.log(INFO, "Хэш от клиента: " + clientHash);
    std::string generatedHash = hashPassword(salt, password);
     logger.log(INFO, "Cравниваю хэши (Сервер == клиент): " + generatedHash + " == " + clientHash );
    return generatedHash == clientHash;
}
