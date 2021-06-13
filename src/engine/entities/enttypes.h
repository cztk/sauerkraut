//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_ENTTYPES_H
#define SAUERKRAUT_ENTTYPES_H

namespace kraut::engine::entities {

    // ET_*: the only static entity types dictated by the engine... rest are gamecode dependent
    enum {
        ET_EMPTY = 0,
        ET_LIGHT,
        ET_MAPMODEL,
        ET_PLAYERSTART,
        ET_ENVMAP,
        ET_PARTICLES,
        ET_SOUND,
        ET_SPOTLIGHT,
        ET_GAMESPECIFIC
    };

    enum                            // static entity types
    {
        NOTUSED = ET_EMPTY,         // entity slot not in use in map
        LIGHT = ET_LIGHT,           // lightsource, attr1 = radius, attr2 = intensity
        MAPMODEL = ET_MAPMODEL,     // attr1 = angle, attr2 = idx
        PLAYERSTART,                // attr1 = angle, attr2 = team
        ENVMAP = ET_ENVMAP,         // attr1 = radius
        PARTICLES = ET_PARTICLES,
        MAPSOUND = ET_SOUND,
        SPOTLIGHT = ET_SPOTLIGHT,
        I_SHELLS, I_BULLETS, I_ROCKETS, I_ROUNDS, I_GRENADES, I_CARTRIDGES,
        I_HEALTH, I_BOOST,
        I_GREENARMOUR, I_YELLOWARMOUR,
        I_QUAD,
        TELEPORT,                   // attr1 = idx, attr2 = model, attr3 = tag
        TELEDEST,                   // attr1 = angle, attr2 = idx
        MONSTER,                    // attr1 = angle, attr2 = monstertype
        CARROT,                     // attr1 = tag, attr2 = type
        JUMPPAD,                    // attr1 = zpush, attr2 = ypush, attr3 = xpush
        BASE,
        RESPAWNPOINT,
        BOX,                        // attr1 = angle, attr2 = idx, attr3 = weight
        BARREL,                     // attr1 = angle, attr2 = idx, attr3 = weight, attr4 = health
        PLATFORM,                   // attr1 = angle, attr2 = idx, attr3 = tag, attr4 = speed
        ELEVATOR,                   // attr1 = angle, attr2 = idx, attr3 = tag, attr4 = speed
        FLAG,                       // attr1 = angle, attr2 = team
        MAXENTTYPES
    };

    enum {
        A_BLUE, A_GREEN, A_YELLOW
    };     // armour types... take 20/40/60 % off
}

#endif //SAUERKRAUT_ENTTYPES_H
