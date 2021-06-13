//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_WEAPONS_H
#define SAUERKRAUT_WEAPONS_H

#include "sounds.h"
#include "../engine/particles/particles.h"

namespace kraut::game {

    // UGH this is fine as a start
    enum {
        GUN_FIST = 0,
        GUN_SG,
        GUN_CG,
        GUN_RL,
        GUN_RIFLE,
        GUN_GL,
        GUN_PISTOL,
        GUN_FIREBALL,
        GUN_ICEBALL,
        GUN_SLIMEBALL,
        GUN_BITE,
        GUN_BARREL,
        NUMGUNS
    };

    class Weapon {

    public:
        int explosion_radius = 0;
        int hitpush = 0;

        constexpr static const struct guninfo { int sound, attackdelay, damage, spread, projspeed, kickamount, range, rays, hitpush, exprad, ttl; const char *name, *file; short part; } guns[NUMGUNS] =
                {
                        { S_PUNCH1,    250,  50,   0,   0,  0,   14,  1,  80,  0,    0, "fist",            "fist",   0 },
                        { S_SG,       1400,  10, 400,   0, 20, 1024, 20,  80,  0,    0, "shotgun",         "shotg",  0 },
                        { S_CG,        100,  30, 100,   0,  7, 1024,  1,  80,  0,    0, "chaingun",        "chaing", 0 },
                        { S_RLFIRE,    800, 120,   0, 320, 10, 1024,  1, 160, 40,    0, "rocketlauncher",  "rocket", 0 },
                        { S_RIFLE,    1500, 100,   0,   0, 30, 2048,  1,  80,  0,    0, "rifle",           "rifle",  0 },
                        { S_FLAUNCH,   600,  90,   0, 200, 10, 1024,  1, 250, 45, 1500, "grenadelauncher", "gl",     0 },
                        { S_PISTOL,    500,  35,  50,   0,  7, 1024,  1,  80,  0,    0, "pistol",          "pistol", 0 },
                        { S_FLAUNCH,   200,  20,   0, 200,  1, 1024,  1,  80, 40,    0, "fireball",        nullptr,     engine::particles::PART_FIREBALL1 },
                        { S_ICEBALL,   200,  40,   0, 120,  1, 1024,  1,  80, 40,    0, "iceball",         nullptr,     engine::particles::PART_FIREBALL2 },
                        { S_SLIMEBALL, 200,  30,   0, 640,  1, 1024,  1,  80, 40,    0, "slimeball",       nullptr,     engine::particles::PART_FIREBALL3 },
                        { S_PIGR1,     250,  50,   0,   0,  1,   12,  1,  80,  0,    0, "bite",            nullptr,     0 },
                        { -1,            0, 120,   0,   0,  0,    0,  1,  80, 40,    0, "barrel",          nullptr,     0 }
                };
    };
}

#endif //SAUERKRAUT_WEAPONS_H
