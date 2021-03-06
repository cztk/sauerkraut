//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_STATES_H
#define SAUERKRAUT_STATES_H
namespace kraut::engine::entities {
    enum {
        CS_ALIVE = 0, CS_DEAD, CS_SPAWNING, CS_LAGGED, CS_EDITING, CS_SPECTATOR
    };

    enum {
        PHYS_FLOAT = 0, PHYS_FALL, PHYS_SLIDE, PHYS_SLOPE, PHYS_FLOOR, PHYS_STEP_UP, PHYS_STEP_DOWN, PHYS_BOUNCE
    };

    enum {
        ENT_PLAYER = 0, ENT_AI, ENT_INANIMATE, ENT_CAMERA, ENT_BOUNCE
    };

    enum {
        COLLIDE_NONE = 0, COLLIDE_ELLIPSE, COLLIDE_OBB, COLLIDE_ELLIPSE_PRECISE
    };
}
#endif //SAUERKRAUT_STATES_H
