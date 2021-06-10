//
// Created by ztk on 2021-06-09.
//

#include "ScriptingHandler.h"

namespace scripting {

    ScriptingHandler::ScriptingHandler(config::Config *pConfig, log::LogHandler *pLogHandler) : _config(pConfig), _logHandler(pLogHandler) {
        initialize();
    }

    ScriptingHandler::~ScriptingHandler() {
        deinitialize();
    }

    void ScriptingHandler::initialize() {

        supportedlanguage libCubeScriptSave{};
        libCubeScriptSave.name = "libcubescript";
        libCubeScriptSave.scriptenginehnd = new LibCubeScript();
        scriptengines.push_back(libCubeScriptSave);
    }

    void ScriptingHandler::deinitialize() {

        for(auto elem: scriptengines) {
            if(elem.name == "libcubescript") {
                delete static_cast<LibCubeScript*>(elem.scriptenginehnd);
            }
        }
    }


    bool ScriptingHandler::execute(const char* filename, const char* scriptinglanguage) {
        for(auto elem: scriptengines) {
            if(elem.name == scriptinglanguage) {
                bool result = static_cast<LibCubeScript*>(elem.scriptenginehnd)->execute(filename);
                if(!result) {
                    _logHandler->log(log::LogLevel::Error, utils::StringHelper::vFormat("could not read \"%s\"", filename));
                }
            }
        }
        return false;
    }

    void ScriptingHandler::bind_var(const char * varname, float *var, bool readonly) {
        for(auto elem: scriptengines) {
            if(elem.name == "libcubescript") {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void ScriptingHandler::bind_var(const char * varname, int *var, bool readonly) {
        for(auto elem: scriptengines) {
            if(elem.name == "libcubescript") {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

    void ScriptingHandler::bind_var(const char * varname, std::string *var, bool readonly) {
        for(auto elem: scriptengines) {
            if(elem.name == "libcubescript") {
                return static_cast<LibCubeScript*>(elem.scriptenginehnd)->bind_var(varname, var, readonly);
            }
        }
    }

}