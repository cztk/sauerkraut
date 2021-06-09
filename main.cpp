#include <iostream>
#include "config/Config.h"
#include "log/LogHandler.h"

int main() {

    Config config;

    ConfigSection test{};
    test.name = "FileLogger";
    test.options.emplace_back(std::pair("filename", "test.log"));

    config.logger.push_back(test);

    auto *logHandler = new LogHandler(&config);

    logHandler->log(0, "test");

    return 0;
}
