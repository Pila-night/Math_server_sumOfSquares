#include "Auth.h"
#include "CLientDataBase.h"
#include "Communicator.h"
#include "HandlerVector.h"
#include "Logger.h"
#include "Server.h"
#include "StatrInterface.h"
#include <UnitTest++/UnitTest++.h>

using namespace std;

SUITE(HelpTest){
TEST(Help) {
 Interface UI;
 int port = 33333;
 const char* argv[] = {"test", "-h", "-p", port, nullptr};
 int argc = sizeof argv / sizeof nullptr - 1;
 REQUIRE CHECK(!iface.Parser(argc, argv));
 CHECK(!iface.getDescription().empty());
 }
}


