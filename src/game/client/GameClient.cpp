//
// Created by ztk on 2021-06-12.
//

#include "GameClient.h"

namespace kraut::game::client {

    GameClient::GameClient(config::Config *pConfig, engine::Engine *pEngine, GameData *pGameData) : _config(pConfig),
                                                                                                    _engine(pEngine),
                                                                                                    _gameData(
                                                                                                            pGameData) {

    }

    void GameClient::initialize() {
        if (_config->dedicated <= 1) {
            //TODO
            player1 = new engine::entities::Player(_engine, _gameData);
            player1->respawn();
            player1->spawnstate(_gameData->gamemode);
            //TODO
            //filtertext(player1->name, "unnamed", false, false, MAXNAMELEN);
            //players.push_back(player1);
            delete player1;
        }
    }
}