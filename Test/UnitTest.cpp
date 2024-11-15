#include "Auth.h"
#include "ClientDataBase.h"
#include "Communicator.h"
#include "HandlerVector.h"
#include "Logger.h"
#include "StartInterface.h"
#include "server.h"
#include "Errors.h"
#include <filesystem>
#include <UnitTest++/UnitTest++.h>
#include <fstream>

                                //Тестирование ServerInterface
// сценарий тестирования справки
SUITE(ServerInterface){
SUITE(HelpTest)
{
    TEST(ShortHelp) //-help
    {
        Interface iface;
        const char* argv[] = { "test", "-h", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(!iface.Parser(argc, argv));
        CHECK(!iface.getDescription().empty());
    }
    TEST(LongHelp)//--help
    {
        Interface iface;
        const char* argv[] = { "test", "--help", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(!iface.Parser(argc, argv));
        CHECK(!iface.getDescription().empty());
    }
    TEST(HelpAndOtherParametr)// несколько параметров
    {
        Interface iface;
        const char* argv[] = { "test", "-h", "-p", "33333", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(!iface.Parser(argc, argv));
        CHECK(!iface.getDescription().empty());
    }
    TEST(ParametrAndHelp)// несколько параметров в другом порядке
    {
        Interface iface;
        const char* argv[] = { "test", "-p", "33333", "-h", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(!iface.Parser(argc, argv));
        CHECK(!iface.getDescription().empty());
    }
    TEST(NoParam) //запуск без параметров
    {
        Interface iface;
        const char* argv[] = { "test",  nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(!iface.Parser(argc, argv));
        CHECK(!iface.getDescription().empty());
    }
}
// сценарий тестирования рабочих параметров
SUITE(WorkParamsTest)
{
    TEST(ShortPort) //короткий параметр -p
    {
        Interface iface;
        const char* argv[] = { "test", "-p", "33333", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(iface.Parser(argc, argv));
        CHECK_EQUAL(iface.getParams().port, 33333);
    }
    TEST(LongPort) //полный параметр --port
    {
        Interface iface;
        const char* argv[] = { "test", "--port", "33333", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(iface.Parser(argc, argv));
        CHECK_EQUAL(iface.getParams().port, 33333);
    }
    TEST(PortAndDataFileAndLogFile)//тестирование сразу нескольких параметров 
    {
        Interface iface;
        std::string DataFile("data.txt");
        std::string LogFile("vlog.log");
        const char* argv[] = { "test", "-p", "33333", "-d", DataFile.c_str(),"-l", LogFile.c_str(), nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(iface.Parser(argc, argv));
        CHECK_EQUAL(iface.getParams().port, 33333);
        CHECK_EQUAL(iface.getParams().dataFileName, "data.txt");
        CHECK_EQUAL(iface.getParams().logFileName, "vlog.log");
        
    }
    TEST(DataFileAndLogFileAndPort) //тестирование сразу нескольких параметров в другом порядке
    {
       Interface iface;
        std::string DataFile("data.txt");
        std::string LogFile("vlog.log");
        const char* argv[] = { "test",  "-d", DataFile.c_str(),"-l", LogFile.c_str(), "-p", "33333", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        REQUIRE CHECK(iface.Parser(argc, argv));
        CHECK_EQUAL(iface.getParams().port, 33333);
        CHECK_EQUAL(iface.getParams().dataFileName, "data.txt");
        CHECK_EQUAL(iface.getParams().logFileName, "vlog.log");
    }
// сценарий тестирования исключений
SUITE(ExceptionTest)
{
    TEST(NoPortValue)
    {
        Interface iface;
        const char* argv[] = { "test", "-p", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        CHECK_THROW(iface.Parser(argc, argv), po::invalid_command_line_syntax);
    }
    TEST(UnknownParam)
    {
        Interface iface;
        const char* argv[] = { "test", "-p", "33333", "-v", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        CHECK_THROW(iface.processCommands(argc, argv), po::unknown_option);
    }
    TEST(InvalidPort)
    {
        Interface iface;
        const char* argv[] = { "test", "-p", "333331", nullptr };
        int argc = sizeof argv / sizeof nullptr - 1;
        CHECK_THROW(iface.processCommands(argc, argv), std::runtime_error);
    }
}
}
}









                                                //Тесты аутентификации
SUITE(Auth) {
    TEST(SaltGenerator) {
        Logger logger("vlog.log");
        logger.open();
        std::ofstream ofs("info.txt");
        ofs << "user:password123" << std::endl;  
        ofs.close(); 
        Authenticator a("info.txt", logger);
        std::string salt1 = a.generateSALT();
        std::string salt2 = a.generateSALT();
        
        CHECK(salt1 != salt2);  
        std::remove("info.txt");
    }

    TEST(hashPassword) {
        Logger logger("vlog.log");
        logger.open();
        std::ofstream ofs("info.txt");
    ofs << "user:password123" << std::endl;  
    ofs.close();  
        Authenticator a("info.txt", logger);
        string salt = "8D35E540D95E394E";
        string hash = "640C3A9DB8F698B955566B21DB073E2141DFD066FBA35247A7D39C4C";
        string pass = "P@ssW0rd";
       string res = a.hashPassword(salt, pass);
       
        CHECK_EQUAL(res, hash);
        std::remove("info.txt");
    }

    TEST(HashEmptyString) { 
        Logger logger("vlog.log");
        logger.open();
        std::ofstream ofs("info.txt");
    ofs << "user:password123" << std::endl;  
    ofs.close();  
        Authenticator a("info.txt", logger);
        string salt = "8D35E540D95E394E";
        string EMPTY = "";
        string res1 = a.hashPassword(salt, EMPTY);
        string res2 = "D3F0F5707F04BA40E4CAAEC58E6806E5B72FB604D6624E23872A2D70";
        CHECK_EQUAL(res1, res2);
        std::remove("info.txt");
    }

    TEST(WhitespaceString) {
        Logger logger("vlog.log");
        logger.open();
        std::ofstream ofs("info.txt");
    ofs << "user:password123" << std::endl;  
    ofs.close(); 
        Authenticator a("info.txt", logger);
       string salt = "8D35E540D95E394E";
        string space = " ";
        string res1 = a.hashPassword(salt, space);
        string res2 = "8EC82336E70482C66111F1C75BD56CC337ECFC6865662331C6B17526";
        CHECK_EQUAL(res1, res2);
        std::remove("info.txt");
    }

    TEST(SpecialCharacters) {
        Logger logger("vlog.log");
        logger.open();
        std::ofstream ofs("info.txt");
        ofs << "user:password123" << std::endl;  
        ofs.close(); 
        Authenticator a("info.txt", logger);
        string salt = "8D35E540D95E394E";
        string SpecialCharacters = "!@#$%^&*()_+{}[];:'\"\,.<>?/";
        string res1 = a.hashPassword(salt, SpecialCharacters);
        string res2 = "021D84278DFABDDEEFCA8CCC0CB5CDD546B28119F47B88062B5D6AC9";
        CHECK_EQUAL(res1, res2);
        std::remove("info.txt");
    }

    TEST(isLoginExistsGood) {
    Logger logger("vlog.log");
    logger.open();
    std::ofstream ofs("info.txt");
    ofs << "user:password123" << std::endl;  
    ofs.close();  
    Authenticator a("info.txt", logger);
    ClientDataBase db("info.txt");
    string login = "user";
    CHECK(db.isLoginExists(login));
    std::remove("info.txt");
    }
     TEST(isLoginExistsBad) {
    Logger logger("vlog.log");
    logger.open();
    std::ofstream ofs("info.txt");
    ofs << "user3:password123" << std::endl;  
    ofs.close();  
    Authenticator a("info.txt", logger);
    ClientDataBase db("info.txt");
    string login = "user";
    CHECK(!(db.isLoginExists(login)));
    std::remove("info.txt");
}
}


                                  //Проверка калькулятора
SUITE(HandlerVector){
 TEST(ProcessVector_NormalCase) {
    HandlerVector handler;
    std::vector<int32_t> input = {-4000, -5000, -6000, -7000};
    int32_t result = handler.processVector(input);
    CHECK_EQUAL(126000000, result); 
}
TEST(ProcessVector_EmptyVector) {
    HandlerVector handler;
    std::vector<int32_t> input = {};
    int32_t result = handler.processVector(input);
    CHECK_EQUAL(0, result); 
}
TEST(ProcessVector_OverflowUp) {
    HandlerVector handler;
    std::vector<int32_t> input = {std::numeric_limits<int32_t>::max(), 1};
    int32_t result = handler.processVector(input);
    CHECK_EQUAL(2147483647, result); 
}
TEST(ProcessVector_SingleElement) {
    HandlerVector handler;
    std::vector<int32_t> input = {5};
    int32_t result = handler.processVector(input);
    CHECK_EQUAL(25, result); 
}
TEST(ProcessVector_LargeInput) {
    HandlerVector handler;
    std::vector<int32_t> vector(1000000, 1); 
    int32_t result = handler.processVector(vector);
    CHECK_EQUAL(1000000, result); 
}
}



                              //Тесты клиентской базы данных
SUITE(ClientDataBaseTests) {
    TEST(LoadDatabase_Success) {
        const std::string test_filename = "test_database.txt";
        {
            std::ofstream file(test_filename);
            file << "user1:password1\n";
            file << "user2:password2\n";
        }
        ClientDataBase db(test_filename);
        CHECK(db.isLoginExists("user1"));
        CHECK(db.isLoginExists("user2"));
        CHECK_EQUAL(db["user1"], "password1");
        CHECK_EQUAL(db["user2"], "password2");
        std::remove(test_filename.c_str());
    }

    TEST(LoadDatabase_EmptyFile) {
        const std::string test_filename = "empty_database.txt";
        {
            std::ofstream file(test_filename);
            file.close();
        }
        CHECK_THROW(ClientDataBase db(test_filename), std::runtime_error);
        std::remove(test_filename.c_str());
    }

    TEST(LoadDatabase_FileNotFound) {
        CHECK_THROW(ClientDataBase db("non_existent_file.txt"), std::system_error);
    }

    TEST(IsLoginExists) {
        const std::string test_filename = "test_login_exists.txt";
        {
            std::ofstream file(test_filename);
            file << "user1:password1\n";
        }
        ClientDataBase db(test_filename);
        CHECK(db.isLoginExists("user1"));
        CHECK(!db.isLoginExists("user2"));
        std::remove(test_filename.c_str());
    }

    TEST(ThrowsExceptionOnEmptyPassword) {
        const std::string test_filename = "test_empty_password.txt";
        {
            std::ofstream file(test_filename);
            file << "user1:" << std::endl; 
        }
        CHECK_THROW(ClientDataBase db(test_filename), DatabaseException);
        std::remove(test_filename.c_str());
    }

    TEST(ThrowsExceptionOnEmptyLogin) {
        const std::string test_filename = "test_empty_login.txt";
        {
            std::ofstream file(test_filename);
            file << ":password123" << std::endl; 
        }
        CHECK_THROW(ClientDataBase db(test_filename), DatabaseException);
        std::remove(test_filename.c_str());
    }
}


SUITE(LoggerTests) {

    TEST(EmptyLogFilePath) {
    CHECK_THROW(Logger logger(""), std::invalid_argument);
}


    TEST(OpenLogFile_Success) {
        const std::string test_filename = "test.log";
        Logger logger(test_filename);
        logger.open();
        CHECK(logger.GetIsOpen());
        std::ifstream file(test_filename);
        CHECK(file.is_open());
        file.close();
        std::remove(test_filename.c_str());
    }

    TEST(LogMessage_Success) {
        const std::string test_filename = "test.log";
        Logger logger(test_filename);
        logger.open();
        logger.log(INFO, "Test log message");
        std::ifstream file(test_filename);
        std::string line;
        bool message_found = false;
        while (std::getline(file, line)) {
            if (line.find("Test log message") != std::string::npos) {
                message_found = true;
                break;
            }
        }
        CHECK(message_found);
        file.close();
        std::remove(test_filename.c_str()); 
    }

    TEST(LogFileNotOpen_Error) {
        Logger logger("test.log");
        CHECK_THROW(logger.log(INFO, "This should not work"), std::runtime_error);
    }

    TEST(CriticalLogMessage_Success) {
    const std::string test_filename = "test.log";
    Logger logger(test_filename);
    logger.open();

    bool exception_thrown = false;
    try {
        logger.log(CRITICAL, "Critical log message");
    } catch (...) {
        exception_thrown = true;
    }
    CHECK(exception_thrown); 
    std::remove(test_filename.c_str()); 
}

}

//Тестирование Server

TEST(ServerCreationSuccess) {
    const std::string test_filename = "test.log";
    Logger logger(test_filename);
    logger.open();
     try {
        Server server(33333, "Test data", logger);
    } catch (...) {
        CHECK(false); 
    }
    std::remove(test_filename.c_str());
}

// Тест на ошибку создания сокета
TEST(ServerSocketError) {
    const std::string test_filename = "test.log";
    Logger logger(test_filename);
    logger.open();
    CHECK_THROW(Server server(-1, "Test data", logger), std::system_error);
    std::remove(test_filename.c_str());
}



int main()
{
 return UnitTest::RunAllTests();
}


