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

    // aka fpsentity
    class Player : public Dynamic {
    public:

        // TODO implement AI
        //ai::aiinfo *ai;
        void *ai;

        Player(Engine *pEngine, game::GameData *pGameData, game::PlayerState *pState);

        ~Player();


        void hitpush(int damage, const Eigen::Vector3d &dir, Player *actor, int gun);

        void stopattacksound();

        void stopidlesound();

        void respawn();

        int respawnwait(int secs, int delay = 0);


        void spawnstate(int gamemode);

        void setlocal(bool b);

    private:
        engine::Engine *_engine;
        game::GameData *_gameData;
        game::PlayerState *_playerState;


    };

}
#endif //SAUERKRAUT_PLAYER_H
