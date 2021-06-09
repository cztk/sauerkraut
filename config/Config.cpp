//
// Created by ztk on 2021-06-09.
//

#include "Config.h"

void config::Config::parseArgs(int argc, char **argv) {




}

void config::Config::parseImportantArgs(int argc, char **argv) {
    // set home dir first
    bool given_homedir = false;
    switch(getopt(argc, argv, "q:")) {
        case 'q':
            given_homedir = true;
            homedir = optarg;
            break;
    }
    if(!given_homedir) {
        homedir = std::string( getenv("HOME") );
    }

    // set log after home dir, but before anything else
    std::string logfile;
    bool given_logfile = false;
    switch(getopt(argc, argv, "g:")) {
        case 'g':
            given_logfile = true;
            logfile = optarg;
            break;
    }
    if(!given_logfile) {
        logfile = "log.txt";
    }

    ConfigSection applicationLog{};
    applicationLog.name = "FileLogger";
    applicationLog.options.emplace_back(std::pair("filename", homedir + std::filesystem::path::preferred_separator + logfile));

    logger.push_back(applicationLog);
}
