//
// Created by ztk on 2021-06-12.
//

#include "NetworkHandler.h"

namespace kraut::network {

    bool NetworkHandler::initialize() {
        bool result = false;
        if(!initialize_enet()) {
            //TODO check deinit parts
            return false;
        }
        return false;
    }

    bool NetworkHandler::initialize_enet() {
        bool result = false;
        if(enet_initialize()<0) {
            enet_time_set(0);
            result = true;
        }
        return result;
    }


}