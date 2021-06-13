//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_GAMECLIENT_H
#define SAUERKRAUT_GAMECLIENT_H

#include "../../engine/engine.h"
#include "../GameData.h"
#include "../../engine/entities/Player.h"

namespace kraut::game::client {

    class GameClient {
    public:
        explicit GameClient(config::Config *pConfig, engine::Engine *pEngine, GameData *pGameData);

        void initialize();

    private:
        config::Config *_config;
        engine::Engine *_engine;
        GameData *_gameData;

        engine::entities::Player *player1 = nullptr;         // our client
    };

}

#endif //SAUERKRAUT_GAMECLIENT_H
