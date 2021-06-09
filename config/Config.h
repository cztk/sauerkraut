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

namespace config {

    struct ConfigSection {
        std::string name;
        std::vector<std::pair<std::string, std::string>> options;
    };

    struct EngineConfig {
    };

    class Config {
    public:
        std::vector<ConfigSection> logger;
        EngineConfig engine{};

        int dedicated = 0;
        std::string homedir;

        void parseArgs(int argc, char **argv);

        void parseImportantArgs(int argc, char **argv);


    };
}

#endif //SAUERKRAUT_CONFIG_H
