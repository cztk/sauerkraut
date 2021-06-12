//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_NETWORKHANDLER_H
#define SAUERKRAUT_NETWORKHANDLER_H

#include <enet/enet.h>

namespace kraut::network {

    class NetworkHandler {

    public:
        bool initialize();

        bool initialize_enet();
    };

}
#endif //SAUERKRAUT_NETWORKHANDLER_H
