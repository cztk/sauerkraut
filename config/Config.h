//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_CONFIG_H
#define SAUERKRAUT_CONFIG_H


#include <string>
#include <vector>

struct ConfigSection {
    std::string name;
    std::pair<std::string, std::string> options;
};

class Config {
public:
    std::vector<ConfigSection> logger;


private:

};


#endif //SAUERKRAUT_CONFIG_H
