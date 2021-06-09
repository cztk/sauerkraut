//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_LOGHANDLER_H
#define SAUERKRAUT_LOGHANDLER_H


#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "../config/Config.h"
#include "loggers/FileLogger.h"
#include "../utils/LockedQueue.h"


class LogHandler {

public:
    explicit LogHandler(Config *pConfig);
    ~LogHandler();
    std::thread run();
    void stop();
    void log(int loglevel, const std::string& text);
private:
    Config *_config;
    std::vector<Logger*> _logger;
    std::mutex _logger_mutex;
    std::mutex _main_mutex;
    std::condition_variable _cv;
    bool _stop = false;
    bool _process = false;
    utils::LockedQueue<std::pair<int, std::string>> messageQueue;

    void initialize();
    void deinitialize();
    void thread_main();
};


#endif //SAUERKRAUT_LOGHANDLER_H
