//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_SCRIPTINGHANDLER_H
#define SAUERKRAUT_SCRIPTINGHANDLER_H

#include "../config/Config.h"
#include "bindings/LibCubeScript.h"

namespace scripting {

    struct supportedlanguage {
        std::string name;
        void* scriptenginehnd;
    };

    class ScriptingHandler {
    public:
        explicit ScriptingHandler(config::Config *pConfig);
        ~ScriptingHandler();

    private:
        config::Config *_config;

        std::vector<supportedlanguage> scriptengines;

        void initialize();
        void deinitialize();
    };

}

#endif //SAUERKRAUT_SCRIPTINGHANDLER_H
