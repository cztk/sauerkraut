//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_RAGDOLL_H
#define SAUERKRAUT_RAGDOLL_H

#include "../entities/Dynamic.h"

namespace kraut::engine::physics {

    class Ragdoll {
    public:
        void cleanragdoll(game::DynamicEntity *dynamicEntity);
    };
}

#endif //SAUERKRAUT_RAGDOLL_H
