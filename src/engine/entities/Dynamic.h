//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_DYNAMIC_H
#define SAUERKRAUT_DYNAMIC_H

#include "Phys.h"
#include "Light.h"
#include "AnimInfo.h"
#include "../engine.h"
#include "../../game/GameData.h"
#include "../physics/Ragdoll.h"

namespace kraut::engine::entities {

    class Dynamic : public Phys { // animated characters, or characters that can receive input
    public:
        bool k_left, k_right, k_up, k_down;         // see input code

        Light light;
        animinterpinfo animinterp[MAXANIMPARTS];
        //TODO ragdoll
        //ragdolldata *ragdoll;
        physics::Ragdoll *ragdoll;
        //TODO octa
        //occludequery *query;
        void *query;
        int lastrendered;
        unsigned char occluded;

        Dynamic();
        ~Dynamic();

        void stopmoving();

        void reset();
    private:

        Eigen::Vector3d abovehead();
    };

}

#endif //SAUERKRAUT_DYNAMIC_H
