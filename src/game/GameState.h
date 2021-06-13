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

        GameState(engine::Engine *pEngine, GameData *pGameData);
        void initialize();

    private:
        engine::Engine *_engine;
        GameData *_gameData;
        engine::entities::Player *player1 = nullptr;         // our client
        std::vector<engine::entities::Player *> players;       // all clients
    };
}

#endif //SAUERKRAUT_GAMESTATE_H
