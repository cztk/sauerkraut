//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_PLAYERSTATE_H
#define SAUERKRAUT_PLAYERSTATE_H

#include <algorithm>

#include "Ai.h"
#include "items.h"
#include "Weapon.h"
#include "gamemodes.h"
#include "../engine/entities/enttypes.h"

namespace kraut::game {

    class PlayerState {
    public:
        int health, maxhealth;
        int armour, armourtype;
        int quadmillis;
        int gunselect, gunwait;
        int ammo[NUMGUNS];
        int aitype, skill;

        PlayerState();

        void baseammo(int gun, int k = 2, int scale = 1);

        void addammo(int gun, int k = 1, int scale = 1);

        bool hasmaxammo(int type);

        bool canpickup(int type);

        void pickup(int type);

        void respawn();

        void spawnstate(int gamemode);

        // just subtract damage here, can set death, etc. later in code calling this
        int dodamage(int damage);

        int hasammo(int gun, int exclude = -1);

    };

}
#endif //SAUERKRAUT_PLAYERSTATE_H
