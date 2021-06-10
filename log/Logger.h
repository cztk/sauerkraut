//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_LOGGER_H
#define SAUERKRAUT_LOGGER_H

#include <string>

namespace log {

    enum class LogLevel
    {
        None = 6,
        Critical = 5,
        Error = 4,
        Warning = 3,
        Info = 2,
        Debug = 1,
        Trace = 0
    };

    class Logger {
    public:
        virtual void init() = 0;

        virtual void deinit() = 0;

        virtual void log(LogLevel loglevel, const std::string &text) = 0;

        virtual ~Logger() = default;
    };

}
#endif //SAUERKRAUT_LOGGER_H
