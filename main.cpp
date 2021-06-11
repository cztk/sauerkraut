#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"




int main(int argc, char **argv) {

    config::Config config{};

    auto *logHandler = new log::LogHandler();
    config.setlogHandler(logHandler);
    auto scriptingHandler = new scripting::ScriptingHandler(&config, logHandler);

    config.parseImportantArgs(argc, argv);
    // TODO bind vars before running first script

    scriptingHandler->initialize("libcubescript", "main");
    scriptingHandler->execute("libcubescript", "main", "init.cfg");
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
