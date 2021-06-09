//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_LOGGER_H
#define SAUERKRAUT_LOGGER_H

class Logger {
public:
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void log(int loglevel, std::string *text) = 0;
    virtual ~Logger() = default;
};

#endif //SAUERKRAUT_LOGGER_H
