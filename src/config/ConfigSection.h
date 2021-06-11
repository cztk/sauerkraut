//
// Created by ztk on 2021-06-10.
//

#ifndef SAUERKRAUT_CONFIGSECTION_H
#define SAUERKRAUT_CONFIGSECTION_H

#include <string>
#include <vector>
namespace config {
    struct ConfigSection {
        std::string name;
        std::vector<std::pair<std::string, std::string>> options;
    };
}
#endif //SAUERKRAUT_CONFIGSECTION_H
