#include <SDL2/SDL.h>

#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"
#include "engine/state.h"


int main(int argc, char **argv) {

    config::Config config{};

    auto logHandler = new krautlog::LogHandler();
    auto logHandlerThread = logHandler->run();
    config.setlogHandler(logHandler);
    auto scriptingHandler = new scripting::ScriptingHandler(&config, logHandler);
    auto scriptingHandlerThread = scriptingHandler->run();

    auto engine_state = new engine::State();

    engine_state->initing = engine::INIT_RESET;

    config.parseImportantArgs(argc, argv);
    // TODO bind vars before running first script

    logHandler->log(krautlog::LogLevel::Info, utils::StringHelper::vFormat("Starting libcubescript engine"));

    config.addScriptingLanguageConfig("libcubescript", "main");

    auto libcubescript_main_config = config.getScriptingLanguageConfig("libcubescript", "main");
    libcubescript_main_config->allow_execute = 1;
    scriptingHandler->initialize(libcubescript_main_config);
    scriptingHandler->execute("libcubescript", "main", "init.cfg");

    logHandler->log(krautlog::LogLevel::Debug, utils::StringHelper::vFormat("Parse args"));
    config.parseArgs(argc, argv);

    engine_state->numcpus = std::clamp(SDL_GetCPUCount(), 1, 96);

    engine_state->initing = engine::NOT_INITING;






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
    delete engine_state;

    return 0;
}
