#include <iostream>
#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"

#include <fstream>
#include <string_view>




int main(int argc, char **argv) {

    config::Config config{};

    auto *logHandler = new log::LogHandler(&config);
    auto scriptingHandler = new scripting::ScriptingHandler(&config, logHandler);

    config.parseImportantArgs(argc, argv);

    // TODO bind vars before running first script
    scriptingHandler->execute("init.cfg", "libcubescript");


    config.parseArgs(argc, argv);


    auto logHandlerThread = logHandler->run();







    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    delete scriptingHandler;
    delete logHandler;

    return 0;
}
