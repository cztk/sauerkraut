//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_SCRIPTINGHANDLER_H
#define SAUERKRAUT_SCRIPTINGHANDLER_H

#include "../config/Config.h"
#include "bindings/LibCubeScript.h"
#include "../log/LogHandler.h"
#include "../utils/stringhelper.h"

namespace scripting {

    struct supportedlanguage {
        std::string name;
        std::string env;
        void* scriptenginehnd;
    };

    class ScriptingHandler {
    public:
        explicit ScriptingHandler(config::Config *pConfig, log::LogHandler *pLogHandler);
        ~ScriptingHandler();

        bool execute(const char* scriptinglanguage, const char* env, const char* filename);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, float *var, bool readonly);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, int *var, bool readonly);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, std::string *var, bool readonly);

        void initialize(const char* scriptinglanguage, const char* env);

    private:
        config::Config *_config;
        log::LogHandler *_logHandler;

        std::vector<supportedlanguage> scriptengines;
        std::mutex _scriptengines_mutex;


        void deinitialize();
    };

}

#endif //SAUERKRAUT_SCRIPTINGHANDLER_H
