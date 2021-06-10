//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_FILELOGGER_H
#define SAUERKRAUT_FILELOGGER_H


#include "../Logger.h"
#include "../../config/Config.h"

namespace log {

    class FileLogger : public Logger {

        struct FileLoggerConfig {
            std::string filename;

        };

    public:
        explicit FileLogger(config::ConfigSection *pConfigSection);

        void init() override;

        void deinit() override;

        virtual void log(LogLevel loglevel, const std::string &text);

    private:
        FILE *_logFile{};
        config::ConfigSection *_configSection;

        FileLoggerConfig _config{};

        void openLog();

        void closeLog();
    };

}

#endif //SAUERKRAUT_FILELOGGER_H
