//
// Created by ztk on 2021-06-13.
//

#include "Dynamic.h"

namespace kraut::engine::entities {
    Dynamic::Dynamic(engine::Engine *pEngine) : ragdoll(nullptr), query(nullptr), lastrendered(0), occluded(0), _engine(pEngine)
    {
        reset();
    }

    Dynamic::~Dynamic()
    {
        if(ragdoll) {
            _engine->ragdoll->cleanragdoll(this);
        }
    }

    void Dynamic::stopmoving()
    {
        k_left = k_right = k_up = k_down = jumping = false;
        move = strafe = 0;
    }

    void Dynamic::reset()
    {
        Phys::reset();
        stopmoving();
        loopi(MAXANIMPARTS) animinterp[i].reset();
    }

    Eigen::Vector3d Dynamic::abovehead() {
        return Eigen::Vector3d(o) + Eigen::Vector3d(0, 0, aboveeye+4);
    }
}