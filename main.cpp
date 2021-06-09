#include <iostream>
#include <zconf.h>
#include "config/Config.h"
#include "log/LogHandler.h"

int main() {

    Config config;

    ConfigSection test{};
    test.name = "FileLogger";
    test.options.emplace_back(std::pair("filename", "test.log"));

    config.logger.push_back(test);

    auto *logHandler = new LogHandler(&config);
    auto logHandlerThread = logHandler->run();

    logHandler->log(0, "test");
    sleep(10);
    logHandler->log(0, "test");
    sleep(10);

    logHandler->stop();
    if(logHandlerThread.joinable()) {
        logHandlerThread.join();
    }

    return 0;
}
