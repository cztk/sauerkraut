//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_OUTLOGGER_H
#define SAUERKRAUT_OUTLOGGER_H

#include <iostream>

#include "../../config/ConfigSection.h"
#include "../Logger.h"

namespace kraut::log {

    template<typename Enumeration>
    auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

    class OutLogger : public Logger {

        struct OutLoggerConfig {

        };

    public:
        explicit OutLogger(config::ConfigSection *pConfigSection);

        void init() override;

        void deinit() override;

        virtual void log(LogLevel loglevel, const std::string &text);

    private:
        FILE *_logFile{};
        config::ConfigSection *_configSection;

        OutLoggerConfig _config{};

        void openLog();

        void closeLog();
    };

}

#endif //SAUERKRAUT_OUTLOGGER_H
