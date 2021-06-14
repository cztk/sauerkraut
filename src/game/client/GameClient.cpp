//
// Created by ztk on 2021-06-12.
//

#include "GameClient.h"

namespace kraut::game::client {

    GameClient::GameClient(config::Config *pConfig, engine::Engine *pEngine, GameData *pGameData, GameState *pGameState) :
    _config(pConfig), _engine(pEngine),  _gameData(pGameData), _gameState(pGameState) {

    }

    void GameClient::initialize() {
        if (_config->dedicated <= 1) {
            //TODO
            player1 = new engine::entities::Player(_engine, _gameData, new PlayerState);
            player1->setlocal(true);
            player1->respawn();
            player1->spawnstate(_gameData->gamemode);
            _gameState->addPlayer(player1);


        }
    }

    void GameClient::deinitialize() {
        if(player1) {
            delete player1;
        }
    }

}