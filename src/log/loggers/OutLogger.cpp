//
// Created by ztk on 2021-06-11.
//

#include "OutLogger.h"

namespace kraut::log {

    OutLogger::OutLogger(config::ConfigSection *pConfigSection) : _configSection(pConfigSection) {

    }

    void OutLogger::log(LogLevel loglevel, const std::string &text) {
        std::cout << as_integer(loglevel) << ": " << text << "\n";
    }

    void OutLogger::init() {

        openLog();
    }

    void OutLogger::deinit() {
        closeLog();
    }

    void OutLogger::openLog() {

    }

    void OutLogger::closeLog() {
        std::cout << std::flush;
    }

}