//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_LOGHANDLER_H
#define SAUERKRAUT_LOGHANDLER_H


#include <string>
#include <mutex>
#include "../config/Config.h"
#include "loggers/FileLogger.h"


class LogHandler {

public:
    explicit LogHandler(Config *pConfig);
    void log(int loglevel, std::string *text);
private:
    Config *_config;
    std::vector<Logger*> logger;

    std::mutex _logger_mutex;

    void initialize();

    void deinitialize();
};


#endif //SAUERKRAUT_LOGHANDLER_H
