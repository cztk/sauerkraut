#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"




int main(int argc, char **argv) {

    config::Config config{};

    auto *logHandler = new log::LogHandler();
    auto logHandlerThread = logHandler->run();
    config.setlogHandler(logHandler);
    auto scriptingHandler = new scripting::ScriptingHandler(&config, logHandler);

    config.parseImportantArgs(argc, argv);
    // TODO bind vars before running first script

    logHandler->log(log::LogLevel::Info, utils::StringHelper::vFormat("Starting libcubescript engine"));
    scriptingHandler->initialize("libcubescript", "main");
    scriptingHandler->execute("libcubescript", "main", "init.cfg");

    logHandler->log(log::LogLevel::Debug, utils::StringHelper::vFormat("Parse args"));
    config.parseArgs(argc, argv);







    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    delete scriptingHandler;
    delete logHandler;

    return 0;
}
