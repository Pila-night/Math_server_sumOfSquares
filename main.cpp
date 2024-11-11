#include "StartInterface.h"

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <system_error>
using namespace std;
namespace po = boost::program_options;

    int main(int argc, const char** argv) {
    try{
    Interface UI;
    UI.processCommands(argc, argv);
    Server server(UI.getPort(), UI.getClientDataFile(), UI.getLogger());
    server.start();

    } catch (const exception& e) { 
        return 1; 
    }

    return 0; 
}
