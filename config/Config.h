//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_CONFIG_H
#define SAUERKRAUT_CONFIG_H


#include <string>
#include <vector>
#include <getopt.h>
#include <filesystem>
#include "../engine/engine.h"
#include "ConfigSection.h"
#include "../log/LogHandler.h"

namespace config {

    struct EngineConfig {
        std::vector<std::string> packagedirs;
        int screen_w = 320;
        int screen_h = 200;
        int screen_depthbits = 24;
        int screen_fsaa = 0;
        int screen_fullscreen = 1;
    };

    struct ServerConfig {
        int dedicated = 0;
        int serveruprate = 0;
        int maxclients = 12;
        std::string serverip = "127.0.0.1";
        int serverport = 28785;
        std::string mastername;
        int updatemaster = 0;
    };

    struct GameConfig {
        int load_firstmap = 0;
        std::string firstmap;
    };

    struct ScriptingLangConfig {
        std::string scriptinglanguage;
        std::string env;
        int allow_execute = 0;

    };

    class Config {
    public:
        std::vector<ConfigSection> logger;
        std::vector<ScriptingLangConfig> _scriptinglangconfigvec;
        std::string homedir;
        std::string initscript;

        EngineConfig engine{};
        ServerConfig server{};
        GameConfig game{};


        void parseArgs(int argc, char **argv);
        void parseImportantArgs(int argc, char **argv);
        void setlogHandler(log::LogHandler *pHandler);

        void addScriptingLanguageConfig(const char *scriptlanguage, const char *env);

        ScriptingLangConfig *getScriptingLanguageConfig(const char *scriptinglanguage, const char *env);

    private:
        log::LogHandler *_loghandler = nullptr;
        std::mutex _scriptinglangconfigvec_mutex;
    };
}

#endif //SAUERKRAUT_CONFIG_H
