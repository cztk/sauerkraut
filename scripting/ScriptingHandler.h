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

        bool do_run_file(const char* filename);
        void bind_var(const char *varname, float *var, bool readonly);
        void bind_var(const char *varname, int *var, bool readonly);
        void bind_var(const char *varname, std::string *var, bool readonly);

    private:
        config::Config *_config;

        std::vector<supportedlanguage> scriptengines;

        void initialize();
        void deinitialize();
    };

}

#endif //SAUERKRAUT_SCRIPTINGHANDLER_H
