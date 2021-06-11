//
// Created by ztk on 2021-06-09.
//

#include "ScriptingHandler.h"

namespace scripting {

    ScriptingHandler::ScriptingHandler(config::Config *pConfig, log::LogHandler *pLogHandler) : _config(pConfig), _logHandler(pLogHandler) {
    }

    ScriptingHandler::~ScriptingHandler() {
        deinitialize();
    }

    void ScriptingHandler::initialize(const char* scriptinglanguage, const char* env) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(scriptinglanguage == elem.name && env == elem.env) {
                return;
            }
        }

        if(strncmp("libcubescript", scriptinglanguage, sizeof(*scriptinglanguage)) == 0) {
            supportedlanguage libCubeScriptSave{};
            libCubeScriptSave.name = "libcubescript";
            libCubeScriptSave.env = env;
            libCubeScriptSave.scriptenginehnd = new LibCubeScript();
            scriptengines.push_back(libCubeScriptSave);
        }


    }

    void ScriptingHandler::deinitialize() {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(elem.name == "libcubescript") {
                delete static_cast<LibCubeScript*>(elem.scriptenginehnd);
            }
        }
        scriptengines.clear();
    }


    bool ScriptingHandler::execute(const char* scriptinglanguage, const char* env, const char* filename) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(elem.name == scriptinglanguage && env == elem.env) {
                bool result = static_cast<LibCubeScript*>(elem.scriptenginehnd)->execute(filename);
                if(!result) {
                    _logHandler->log(log::LogLevel::Error, utils::StringHelper::vFormat("could not read \"%s\"", filename));
                }
            }
        }
        return false;
    }

    void ScriptingHandler::bind_var(const char* scriptinglanguage, const char* env, const char * varname, float *var, bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(elem.name == "libcubescript" && elem.name == scriptinglanguage && elem.env == env) {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void ScriptingHandler::bind_var(const char* scriptinglanguage, const char* env, const char * varname, int *var, bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(elem.name == "libcubescript" && elem.name == scriptinglanguage && elem.env == env) {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void ScriptingHandler::bind_var(const char* scriptinglanguage, const char* env, const char * varname, std::string *var, bool readonly) {
        std::unique_lock<std::mutex> lock(_scriptengines_mutex);
        for(const auto& elem: scriptengines) {
            if(elem.name == "libcubescript" && elem.name == scriptinglanguage && elem.env == env) {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

}