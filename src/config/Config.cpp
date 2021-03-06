//
// Created by ztk on 2021-06-09.
//

#include "Config.h"

namespace kraut::config {

    void config::Config::parseArgs(int argc, char **argv) {
        int opt;
        while ((opt = getopt(argc, argv, "q:rk:g:d:w:h:z:ba:vt:sfl:m:j:i:c:u:")) != -1) {
            switch (opt) {
                //clientoption
                case 'q':
                    if (homedir[0]) {
                        if (nullptr != _loghandler) {
                            _loghandler->log(log::LogLevel::Info,
                                             utils::StringHelper::vFormat("Using home directory: %s",
                                                                          homedir.c_str()));
                        }
                    }
                    break;
                case 'r': /* compat, ignore */
                    break;
                case 'k': {
                    _loghandler->log(log::LogLevel::Info,
                                     utils::StringHelper::vFormat("Adding package directory: %s", optarg));
                    engine.packagedirs.emplace_back(optarg);
                    break;
                }
                case 'g':
                    break;
                case 'd':
                    dedicated = atoi(optarg);
                    if (dedicated <= 0) {
                        dedicated = 2;
                    }
#ifdef KRAUT_LOG_DEBUG
                    _loghandler->log(log::LogLevel::Debug, utils::StringHelper::vFormat("Setting dedicated to: %i", dedicated));
#endif
                    break;
                case 'w':
                    engine.screen_w = std::clamp(atoi(optarg), engine::SCREEN_MINW, engine::SCREEN_MAXW);
                    break;
                case 'h':
                    engine.screen_h = std::clamp(atoi(optarg), engine::SCREEN_MINH, engine::SCREEN_MAXH);
                    break;
                case 'z':
                    engine.screen_depthbits = atoi(optarg);
                    break;
                case 'b': /* compat, ignore */ break;
                case 'a':
                    engine.screen_fsaa = atoi(optarg);
                    break;
                case 'v': /* compat, ignore */ break;
                case 't':
                    engine.screen_fullscreen = atoi(optarg);
                    break;
                case 's': /* compat, ignore */ break;
                case 'f': /* compat, ignore */ break;
                case 'l': {
                    game.load_firstmap = 1;
                    game.firstmap = optarg;
                    break;
                }
                case 'x':
                    initscript = optarg;
                    break;
                    //serveroption
                case 'u':
                    server.serveruprate = atoi(optarg);
                    break;
                case 'c':
                    server.maxclients = atoi(optarg);
                    break;
                case 'i':
                    server.serverip = optarg;
                    break;
                case 'j':
                    server.serverport = atoi(optarg);
                    break;
                case 'm':
                    server.mastername = optarg;
                    if (server.mastername[0]) {
                        server.updatemaster = 1;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    void config::Config::parseImportantArgs(int argc, char **argv) {
        int opt;
        // set home dir first
        bool given_homedir = false;

        std::string logfile;
        bool given_logfile = false;

        while ((opt = getopt(argc, argv, "q:")) != -1) {
            if ('q' == opt) {
                given_homedir = true;
                homedir = optarg;
                continue;
            }
            if ('g' == opt) {
                given_logfile = true;
                logfile = optarg;
            }
        }
        if (!given_homedir) {
            homedir = std::string(getenv("HOME"));
        }

        // set log after home dir, but before anything else
        if (!given_logfile) {
            logfile = "log.txt";
        }

        _loghandler->log(log::LogLevel::Info,
                         utils::StringHelper::vFormat("Using log file: %s%c%s", homedir.c_str(),
                                                      std::filesystem::path::preferred_separator, logfile.c_str()));

        ConfigSection applicationLog{};
        applicationLog.name = "FileLogger";
        applicationLog.options.emplace_back(
                std::pair("filename", homedir + std::filesystem::path::preferred_separator + logfile));
        _loghandler->initialize(applicationLog);
        logger.push_back(applicationLog);
    }

    void config::Config::setlogHandler(log::LogHandler *pHandler) {

        _loghandler = pHandler;

        ConfigSection applicationLog{};
        applicationLog.name = "OutLogger";
        _loghandler->initialize(applicationLog);
        logger.push_back(applicationLog);

        _loghandler = pHandler;
    }

    void config::Config::addScriptingLanguageConfig(const char *scriptlanguage, const char *env) {
        std::unique_lock<std::mutex> lk(_scriptinglangconfigvec_mutex);
        ScriptingLangConfig scriptingLangConfig{};
        scriptingLangConfig.scriptinglanguage = scriptlanguage;
        scriptingLangConfig.env = env;
        _scriptinglangconfigvec.push_back(scriptingLangConfig);

    }

    config::ScriptingLangConfig *
    config::Config::getScriptingLanguageConfig(const char *scriptinglanguage, const char *env) {
        std::unique_lock<std::mutex> lk(_scriptinglangconfigvec_mutex);
        auto result = std::find_if(
                _scriptinglangconfigvec.begin(), _scriptinglangconfigvec.end(),
                [scriptinglanguage, env](auto const &a) {
                    return (a.scriptinglanguage == scriptinglanguage && a.env == env);
                });
        if (result == _scriptinglangconfigvec.end()) {
            return nullptr;
        } else return &(*result);
    }
}