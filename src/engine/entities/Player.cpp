//
// Created by ztk on 2021-06-12.
//

#include "Player.h"

namespace kraut::engine::entities {

    Player::Player(Engine *pEngine, game::GameData *pGameData, game::PlayerState *pState) : _engine(pEngine), _gameData(pGameData), _playerState(pState) {
        respawn();
    }

    Player::~Player() {
        //TODO
        //freeeditinfo(edit);
        if (_playerState->attackchan >= 0) {
            _engine->engine_hal_hnd->soundHandler->stopsound(_playerState->attacksound, _playerState->attackchan, 0);
        }
        if (_playerState->idlechan >= 0) {
            _engine->engine_hal_hnd->soundHandler->stopsound(_playerState->idlesound, _playerState->idlechan, 0);
        }
        //TODO implement ai
        //if(ai) delete ai;
    }

    void Player::hitpush(int damage, const Eigen::Vector3d &dir, Player *actor, int gun) {
        Eigen::Vector3d push(dir);
        push *= (
                (actor == this && game::Weapon::guns[gun].exprad ? _playerState->explosion_selfpush : 1.0f) *
                        game::Weapon::guns[gun].hitpush * damage / _playerState->weight
        );
        vel += push;
    }

    void Player::stopattacksound() {
        if (_playerState->attackchan >= 0) {
            _engine->engine_hal_hnd->soundHandler->stopsound(_playerState->attacksound, _playerState->attackchan, 250);
        }
        _playerState->attacksound = _playerState->attackchan = -1;
    }

    void Player::stopidlesound() {
        if (_playerState->idlechan >= 0) {
            _engine->engine_hal_hnd->soundHandler->stopsound(_playerState->idlesound, _playerState->idlechan, 100);
        }
        _playerState->idlesound = _playerState->idlechan = -1;
    }

    void Player::respawn() {
        Dynamic::reset();
        _playerState->respawn();
        stopattacksound();
    }

    int Player::respawnwait(int secs, int delay) {
        return std::max(0, secs - (_engine->lastmillis - _playerState->lastpain - delay) / 1000);
    }

    void Player::spawnstate(int gamemode) {
        _playerState->spawnstate(gamemode);

    }

    void Player::setlocal(bool b) {
        _playerState->local = true;

    }

}