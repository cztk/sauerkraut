#include <iostream>
#include "config/Config.h"
#include "log/LogHandler.h"

int main() {

    Config config;
    LogHandler *logHandler = new LogHandler(&config);

    return 0;
}
