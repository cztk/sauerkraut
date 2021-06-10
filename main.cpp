#include <iostream>
#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"

#include <fstream>
#include <string_view>




int main(int argc, char **argv) {

    config::Config config{};

    config.parseImportantArgs(argc, argv);

    config.parseArgs(argc, argv);

    auto *logHandler = new log::LogHandler(&config);
    auto logHandlerThread = logHandler->run();

    auto scriptingHandler = new scripting::ScriptingHandler(&config);





    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    delete scriptingHandler;
    delete logHandler;

    return 0;
}
