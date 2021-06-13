//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_PLAYERSTATE_H
#define SAUERKRAUT_PLAYERSTATE_H

#include "Weapon.h"

namespace kraut::game {

    class PlayerState {
    public:
        int health, maxhealth;
        int armour, armourtype;
        int quadmillis;
        int gunselect, gunwait;
        int ammo[NUMGUNS];
        int aitype, skill;

        void respawn();

    };

}
#endif //SAUERKRAUT_PLAYERSTATE_H
