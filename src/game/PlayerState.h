//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_PLAYERSTATE_H
#define SAUERKRAUT_PLAYERSTATE_H

#include <algorithm>
#include <eigen3/Eigen/Core>

#include "Ai.h"
#include "Auth.h"
#include "items.h"
#include "Weapon.h"
#include "gamemodes.h"
#include "../engine/entities/enttypes.h"

namespace kraut::game {
    enum
    {
        TRIGGER_RESET = 0,
        TRIGGERING,
        TRIGGERED,
        TRIGGER_RESETTING,
        TRIGGER_DISAPPEARED
    };

    class PlayerState {
    public:
        int clientnum = -1;
        int privilege = game::PRIV_NONE;
        int lastupdate = 0;
        int plag = 0;
        int ping = 0;
        int lifesequence = 0;                   // sequence id for each respawn, used in damage test
        int respawned = -1;
        int suicided = -1;
        int lastpain = 0;
        int triggerstate = TRIGGER_RESET;
        int lasttrigger = 0;
        int lastaction{}, lastattackgun{};
        bool attacking{};

        int weight = 100;                         // affects the effectiveness of hitpush
        float explosion_selfpush = 2.5f;
        int ownernum{}, lastnode{};
        Eigen::Vector3d muzzle;
        // TODO get from physent
        Eigen::Vector3d vel;
        int attacksound = -1;
        int attackchan = -1;
        int idlesound = -1;
        int idlechan = -1;
        int lasttaunt{};
        int lastpickup{}, lastpickupmillis{}, lastbase{}, lastrepammo{}, flagpickup{}, tokens{};
        Eigen::Vector3d lastcollect;
        int frags = 0;
        int flags = 0;
        int deaths = 0;
        int totaldamage = 0;
        int totalshots = 0;
        //TODO editinfo
        // editinfo *edit;
        void *edit = nullptr;
        float deltayaw{}, deltapitch{}, deltaroll{}, newyaw{}, newpitch{}, newroll{};
        int smoothmillis = 0;

        std::string name ="unnamed";
        std::string team;
        std::string info;
        int playermodel = -1;

        int health{};
        int maxhealth = 100;
        int armour{}, armourtype{};
        int quadmillis{};
        int gunselect{}, gunwait{};
        int ammo[NUMGUNS]{};
        bool local = false;
        int aitype = AI_NONE; //TODO hmmm
        int aiskill = 0;

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
