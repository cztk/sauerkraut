#include "config/Config.h"
#include "log/LogHandler.h"
#include "scripting/ScriptingHandler.h"
#include "engine/state.h"
#include "engine/hal/HalHandler.h"
#include "engine/engine.h"

int main(int argc, char **argv) {

    kraut::config::Config config{};
    auto logHandler = new kraut::log::LogHandler();
    auto logHandlerThread = logHandler->run();
    config.setlogHandler(logHandler);
#ifdef KRAUT_LOG_TRACE
    logHandler->log(log::LogLevel::Trace, utils::StringHelper::vFormat("Starting scripting handler"));
#endif
    auto scriptingHandler = new kraut::scripting::ScriptingHandler(&config, logHandler);
    auto scriptingHandlerThread = scriptingHandler->run();

    auto engine_state = new kraut::engine::State();
    kraut::config::ScriptingLangConfig *libcubescript_main_config = nullptr;

    engine_state->initing = kraut::engine::INIT_RESET;

    config.parseImportantArgs(argc, argv);
    // TODO bind vars before running first script

    logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("Starting libcubescript engine"));
    config.addScriptingLanguageConfig("libcubescript", "main");
    libcubescript_main_config = config.getScriptingLanguageConfig("libcubescript", "main");
    libcubescript_main_config->allow_execute = 1;
    scriptingHandler->initialize(libcubescript_main_config);
    scriptingHandler->execute("libcubescript", "main", "init.cfg");
#ifdef KRAUT_LOG_DEBUG
    logHandler->log(log::LogLevel::Debug, utils::StringHelper::vFormat("Parse args"));
#endif
    config.parseArgs(argc, argv);

    engine_state->numcpus = std::clamp(std::thread::hardware_concurrency(), 1u, 96u);
#ifdef KRAUT_LOG_DEBUG
    logHandler->log(log::LogLevel::Debug, utils::StringHelper::vFormat("found number of cores: %l", engine_state->numcpus));
#endif
    engine_state->initing = kraut::engine::NOT_INITING;


    kraut::engine::Engine krautengine(engine_state, &config, logHandler);

    if(krautengine.initialize()) {







    }
    krautengine.deinitialize();



    scriptingHandler->stop();
    if (scriptingHandlerThread.joinable()) {
        scriptingHandlerThread.join();
    }

    logHandler->stop();
    if (logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    delete scriptingHandler;
    delete logHandler;
    delete engine_state;

    return 0;
}