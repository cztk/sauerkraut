//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_GAMESTATE_H
#define SAUERKRAUT_GAMESTATE_H

#include <vector>
#include "GameData.h"
#include "../engine/entities/Player.h"


namespace kraut::game {

#define MAXNAMELEN 15
#define MAXTEAMLEN 4

    class GameState {

    public:

        GameState(config::Config *pConfig, engine::Engine *pEngine, GameData *pGameData);

        void initialize();

        void addPlayer(engine::entities::Player *pPlayer);

    private:
        config::Config *_config;
        engine::Engine *_engine;
        GameData *_gameData;

        std::vector<engine::entities::Player *> players;       // all clients
    };
}

#endif //SAUERKRAUT_GAMESTATE_H
