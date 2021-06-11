#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"




int main(int argc, char **argv) {

    config::Config config{};

    auto logHandler = new log::LogHandler();
    auto logHandlerThread = logHandler->run();
    config.setlogHandler(logHandler);
    auto scriptingHandler = new scripting::ScriptingHandler(&config, logHandler);
    auto scriptingHandlerThread = scriptingHandler->run();

    config.parseImportantArgs(argc, argv);
    // TODO bind vars before running first script

    logHandler->log(log::LogLevel::Info, utils::StringHelper::vFormat("Starting libcubescript engine"));

    config.addScriptingLanguageConfig("libcubescript", "main");

    auto libcubescript_main_config = config.getScriptingLanguageConfig("libcubescript", "main");
    scriptingHandler->initialize(libcubescript_main_config);
    scriptingHandler->execute("libcubescript", "main", "init.cfg");

    logHandler->log(log::LogLevel::Debug, utils::StringHelper::vFormat("Parse args"));
    config.parseArgs(argc, argv);






    scriptingHandler->stop();
    if(scriptingHandlerThread.joinable()) {
        scriptingHandlerThread.join();
    }

    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    delete scriptingHandler;
    delete logHandler;

    return 0;
}
