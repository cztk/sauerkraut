//
// Created by ztk on 2021-06-12.
//

#include "GameState.h"

namespace kraut::game {

    GameState::GameState(config::Config *pConfig, engine::Engine *pEngine, GameData *pGameData) : _config(pConfig),
                                                                                                  _engine(pEngine),
                                                                                                  _gameData(pGameData) {

    }

    void GameState::initialize() {

    }

    void GameState::addPlayer(engine::entities::Player *pPlayer) {
        players.push_back(pPlayer);
    }


}