//
// Created by ztk on 2021-06-12.
//

#include "GameState.h"

namespace kraut::game {

    GameState::GameState(engine::Engine *pEngine, GameData *pGameData) : _engine(pEngine), _gameData(pGameData) {

    }

    void GameState::initialize() {
        //TODO
        //player1 = spawnstate(new engine::entities::Player(_engine, _gameData));
        //TODO
        //filtertext(player1->name, "unnamed", false, false, MAXNAMELEN);
        players.push_back(player1);
    }


}