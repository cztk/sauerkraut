//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_LOGHANDLER_H
#define SAUERKRAUT_LOGHANDLER_H


#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Logger.h"
#include "../utils/LockedQueue.h"
#include "../config/ConfigSection.h"


namespace log {

    class LogHandler {

    public:
        explicit LogHandler();
        ~LogHandler();
        std::thread run();
        void stop();
        void initialize(config::ConfigSection loggerconf);
        void log(log::LogLevel loglevel, const std::string& text);

    private:
        std::vector<Logger *> _logger;
        std::mutex _logger_mutex;
        std::mutex _main_mutex;
        std::condition_variable _cv;
        bool _stop = false;
        bool _process = false;
        utils::LockedQueue<std::pair<LogLevel, std::string>> messageQueue;
        void deinitialize();

        void thread_main();
    };

}

#endif //SAUERKRAUT_LOGHANDLER_H
