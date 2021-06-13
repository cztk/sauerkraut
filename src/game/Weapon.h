//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_WEAPONS_H
#define SAUERKRAUT_WEAPONS_H

namespace kraut::game {

    // UGH this is fine as a start
    enum { GUN_FIST = 0, GUN_SG, GUN_CG, GUN_RL, GUN_RIFLE, GUN_GL, GUN_PISTOL, GUN_FIREBALL, GUN_ICEBALL, GUN_SLIMEBALL, GUN_BITE, GUN_BARREL, NUMGUNS };

    class Weapon {

    public:
        int explosion_radius = 0;
        int hitpush = 0;

    };
}

#endif //SAUERKRAUT_WEAPONS_H
