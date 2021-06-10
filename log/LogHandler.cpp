//
// Created by ztk on 2021-06-09.
//

#include "LogHandler.h"
#include "loggers/FileLogger.h"

namespace log {
    LogHandler::LogHandler(config::Config *pConfig) : _config(pConfig) {
        initialize();
    }

    LogHandler::~LogHandler() {
        deinitialize();
    }

    void LogHandler::log(LogLevel loglevel, const std::string& text) {
        messageQueue.push(std::pair(loglevel, text));
        _process = true;
        _cv.notify_one();
    }

    void LogHandler::initialize() {
        // TODO: something reflection like implementation
        std::unique_lock<std::mutex> lock(_logger_mutex);
        for (auto &loggerconf: _config->logger) {
            if ("FileLogger" == loggerconf.name) {
                auto *actlogger = new FileLogger(&loggerconf);
                actlogger->init();
                _logger.push_back(actlogger);
            }
        }
    }

    void LogHandler::deinitialize() {
        std::unique_lock<std::mutex> lock(_logger_mutex);
        for (auto actlogger: _logger) {
            actlogger->deinit();
            delete actlogger;
        }
        _logger.clear();

    }

    std::thread LogHandler::run() {
        return std::thread([this] { this->thread_main(); });
    }

    void LogHandler::thread_main() {
        initialize();

        while (!_stop) {
            std::unique_lock<std::mutex> lk(_main_mutex);
            _cv.wait(lk, [this] { return _process || _stop; });

            if (!messageQueue.empty()) {
                while (!messageQueue.empty()) {
                    auto entry = messageQueue.pop();
                    for (auto const &obj : _logger) {
                        obj->log(entry.first, entry.second);
                    }
                }
            }
            _process = false;
            lk.unlock();
        }

    }

    void LogHandler::stop() {
        {
            _stop = true;
            _cv.notify_one();
        }
    }
}