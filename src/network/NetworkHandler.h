//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_NETWORKHANDLER_H
#define SAUERKRAUT_NETWORKHANDLER_H

#include <enet/enet.h>
#include "../utils/stringhelper.h"
#include "../log/LogHandler.h"

namespace kraut::network {

    class NetworkHandler {

    public:
        explicit NetworkHandler(log::LogHandler *pLogHandler);

        bool initialize();

        void deinitialize();

    private:
        bool initialize_enet();

        log::LogHandler *_logHandler;
    };

}
#endif //SAUERKRAUT_NETWORKHANDLER_H
