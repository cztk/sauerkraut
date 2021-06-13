//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_PLAYER_H
#define SAUERKRAUT_PLAYER_H

#include <string>
#include <eigen3/Eigen/Dense>
#include "../../game/Auth.h"
#include "../engine.h"
#include "../../game/GameData.h"
#include "../../game/PlayerState.h"
#include "Phys.h"
#include "Dynamic.h"
#include "../../game/Weapon.h"

namespace kraut::engine::entities {

    // aka fpsent
    class Player : public Dynamic, public game::PlayerState {
    public:
        int weight;                         // affects the effectiveness of hitpush
        int clientnum, privilege, lastupdate, plag, ping;
        int lifesequence;                   // sequence id for each respawn, used in damage test
        int respawned, suicided;
        int lastpain;
        int lastaction, lastattackgun;
        bool attacking;
        int attacksound, attackchan, idlesound, idlechan;
        int lasttaunt;
        int lastpickup, lastpickupmillis, lastbase, lastrepammo, flagpickup, tokens;
        Eigen::Vector3d lastcollect;
        int frags, flags, deaths, totaldamage, totalshots;
        //TODO editinfo
        // editinfo *edit;
        void *edit;
        float deltayaw, deltapitch, deltaroll, newyaw, newpitch, newroll;
        int smoothmillis;

        std::string name, team, info;
        int playermodel;
        // TODO implement AI
        //ai::aiinfo *ai;
        void *ai;
        int ownernum, lastnode;

        Eigen::Vector3d muzzle;

        // TODO get from physent
        Eigen::Vector3d vel;

        Player(engine::Engine *pEngine, game::GameData *pGameData);

        ~Player();


        void hitpush(int damage, const Eigen::Vector3d &dir, Player *actor, int gun);

        void stopattacksound();

        void stopidlesound();

        void respawn();

        int respawnwait(int secs, int delay = 0);

        float explosion_selfpush = 2.5f;

    private:
        engine::Engine *_engine;
        game::GameData *_gameData;


    };

}
#endif //SAUERKRAUT_PLAYER_H
