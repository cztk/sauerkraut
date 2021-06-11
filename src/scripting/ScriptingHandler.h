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
        config::ScriptingLangConfig *config;
        void* scriptenginehnd;
    };

    class ScriptingHandler {
    public:
        explicit ScriptingHandler(config::Config *pConfig, krautlog::LogHandler *pLogHandler);
        ~ScriptingHandler();

        std::thread run();
        void stop();

        bool execute(const char* scriptinglanguage, const char* env, const char* filename);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, float *var, bool readonly);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, int *var, bool readonly);
        void bind_var(const char* scriptinglanguage, const char* env, const char *varname, std::string *var, bool readonly);

        void initialize(config::ScriptingLangConfig *scriptingLangConfig);

    private:
        config::Config *_config;
        krautlog::LogHandler *_logHandler;

        std::vector<supportedlanguage> scriptengines;
        std::mutex _scriptengines_mutex;
        std::mutex _main_mutex;
        std::condition_variable _cv;
        bool _stop = false;
        bool _process = false;

        void thread_main();
        void deinitialize();
    };

}

#endif //SAUERKRAUT_SCRIPTINGHANDLER_H
