//
// Created by ztk on 2021-06-09.
//

#include "ScriptingHandler.h"

namespace scripting {

    ScriptingHandler::ScriptingHandler(config::Config *pConfig) : _config(pConfig) {
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
}