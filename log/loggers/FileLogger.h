//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_FILELOGGER_H
#define SAUERKRAUT_FILELOGGER_H


#include "../Logger.h"
#include "../../config/Config.h"

class FileLogger : public Logger {

public:
    explicit FileLogger(Config *pConfig);
    virtual void init();
    virtual void deinit();
    virtual void log(int loglevel, std::string *text);
};


#endif //SAUERKRAUT_FILELOGGER_H
