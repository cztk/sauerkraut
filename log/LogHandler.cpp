//
// Created by ztk on 2021-06-09.
//

#include "LogHandler.h"

LogHandler::LogHandler(Config *pConfig) : _config(pConfig) {

}

void LogHandler::log(int loglevel, std::string *text) {

}

void LogHandler::initialize() {
    // TODO: something reflection like implementation
    std::unique_lock<std::mutex> lock(_logger_mutex);
    for(auto const& loggerconf: _config->logger) {
        if("FileLogger" == loggerconf.name) {
            auto *actlogger = new FileLogger(_config);
            logger.push_back(actlogger);
        }
    }
}

void LogHandler::deinitialize() {
    std::unique_lock<std::mutex> lock(_logger_mutex);
    for(auto actlogger: logger) {
        actlogger->deinit();
        delete actlogger;
    }
    logger.clear();

}