//
// Created by ztk on 2021-06-09.
//
#include "ScriptingHandler.h"

namespace kraut::scripting {


    ScriptingHandler::ScriptingHandler(config::Config *pConfig, log::LogHandler *pLogHandler) : _config(
            pConfig),
                                                                                                _logHandler(
                                                                                                        pLogHandler) {
    }

    ScriptingHandler::~ScriptingHandler() {
        deinitialize();
    }

    void ScriptingHandler::initialize(config::ScriptingLangConfig *scriptingLangConfig) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (scriptingLangConfig->scriptinglanguage == elem.config->scriptinglanguage &&
                scriptingLangConfig->env == elem.config->env) {
                return;
            }
        }

        if ("libcubescript" == scriptingLangConfig->scriptinglanguage) {
            supportedlanguage libCubeScriptSave{};
            libCubeScriptSave.config = scriptingLangConfig;
            libCubeScriptSave.scriptenginehnd = new LibCubeScript();
            scriptengines.push_back(libCubeScriptSave);
        }


    }

    void ScriptingHandler::deinitialize() {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (elem.config->scriptinglanguage == "libcubescript") {
                delete static_cast<LibCubeScript *>(elem.scriptenginehnd);
            }
        }
        scriptengines.clear();
    }


    bool ScriptingHandler::execute(const char *scriptinglanguage, const char *env, const char *filename) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (elem.config->scriptinglanguage == scriptinglanguage && env == elem.config->env) {
                if (0 == elem.config->allow_execute) {
                    _logHandler->log(log::LogLevel::Error,
                                     utils::StringHelper::vFormat("Not allowed to execute \"%s\" for %s in env %s",
                                                                  filename, scriptinglanguage, env));
                    return false;
                }
                bool result = static_cast<LibCubeScript *>(elem.scriptenginehnd)->execute(filename);
                if (!result) {
                    _logHandler->log(log::LogLevel::Error,
                                     utils::StringHelper::vFormat("could not execute \"%s\"", filename));
                }
                return result;
            }
        }
        return false;
    }

    void ScriptingHandler::bind_var(const char *scriptinglanguage, const char *env, const char *varname, float *var,
                                    bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (elem.config->scriptinglanguage == scriptinglanguage && env == elem.config->env) {
                return static_cast<LibCubeScript *>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void ScriptingHandler::bind_var(const char *scriptinglanguage, const char *env, const char *varname, int *var,
                                    bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (elem.config->scriptinglanguage == scriptinglanguage && env == elem.config->env) {
                return static_cast<LibCubeScript *>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void
    ScriptingHandler::bind_var(const char *scriptinglanguage, const char *env, const char *varname,
                               std::string *var,
                               bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for (const auto &elem: scriptengines) {
            if (elem.config->scriptinglanguage == scriptinglanguage && env == elem.config->env) {
                return static_cast<LibCubeScript *>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    std::thread ScriptingHandler::run() {
        return std::thread([this] { this->thread_main(); });
    }

    void ScriptingHandler::thread_main() {

        while (!_stop) {
            std::unique_lock<std::mutex> lk(_main_mutex);
            _cv.wait(lk, [this] { return _process || _stop; });


            _process = false;
            lk.unlock();
        }

    }

    void ScriptingHandler::stop() {
        {
            _stop = true;
            _cv.notify_one();
        }
    }
}