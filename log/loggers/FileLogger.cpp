//
// Created by ztk on 2021-06-09.
//

#include "FileLogger.h"

namespace log {

    FileLogger::FileLogger(config::ConfigSection *pConfigSection) : _configSection(pConfigSection) {

    }

    void FileLogger::log(LogLevel loglevel, const std::string &text) {
        if (nullptr != _logFile) {
            fputs(text.c_str(), _logFile);
        }
    }

    void FileLogger::init() {

        for (auto const &option: _configSection->options) {
            if ("filename" == option.first) {
                _config.filename = option.second;
            }
        }

        openLog();
    }

    void FileLogger::deinit() {
        closeLog();
    }

    void FileLogger::openLog() {
        _logFile = fopen(_config.filename.c_str(), "a+");
    }

    void FileLogger::closeLog() {
        fclose(_logFile);
    }

}