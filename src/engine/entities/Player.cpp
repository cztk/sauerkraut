//
// Created by ztk on 2021-06-12.
//

#include "Player.h"

namespace kraut::engine::entities {

    Player::Player(engine::Engine *pEngine, game::GameData *pGameData) :
    weight(100), clientnum(-1), privilege(game::PRIV_NONE), lastupdate(0), plag(0), ping(0), lifesequence(0), respawned(-1),
    suicided(-1), lastpain(0), attacksound(-1), attackchan(-1), idlesound(-1), idlechan(-1), frags(0), flags(0),
    deaths(0), totaldamage(0), totalshots(0), edit(NULL), smoothmillis(-1), playermodel(-1), ai(nullptr), ownernum(-1),
    muzzle(-1, -1, -1), _engine(pEngine), _gameData(pGameData)
    {
        respawn();
    }
    Player::~Player()
    {
        //TODO
        //freeeditinfo(edit);
        if(attackchan >= 0){
            _engine->engine_hal_hnd->soundHandler->stopsound(attacksound, attackchan, 0);
        }
        if(idlechan >= 0){
            _engine->engine_hal_hnd->soundHandler->stopsound(idlesound, idlechan, 0);
        }
        //TODO implement ai
        //if(ai) delete ai;
    }

    void Player::hitpush(int damage, const Eigen::Vector3d &dir, Player *actor, int gun)
    {
        Eigen::Vector3d push(dir);
        push *= (
                (actor==this && _gameData->getWeapon(gun)->explosion_radius ? explosion_selfpush : 1.0f) * _gameData->getWeapon(gun)->hitpush*damage / weight
                );
        vel += push;
    }

    void Player::stopattacksound()
    {
        if(attackchan >= 0){
            _engine->engine_hal_hnd->soundHandler->stopsound(attacksound, attackchan, 250);
        }
        attacksound = attackchan = -1;
    }

    void Player::stopidlesound()
    {
        if(idlechan >= 0){
            _engine->engine_hal_hnd->soundHandler->stopsound(idlesound, idlechan, 100);
        }
        idlesound = idlechan = -1;
    }

    void Player::respawn()
    {
        Dynamic::reset();
        game::PlayerState::respawn();
        respawned = suicided = -1;
        lastaction = 0;
        lastattackgun = gunselect;
        attacking = false;
        lasttaunt = 0;
        lastpickup = -1;
        lastpickupmillis = 0;
        lastbase = lastrepammo = -1;
        flagpickup = 0;
        tokens = 0;
        lastcollect = Eigen::Vector3d(-1e10f, -1e10f, -1e10f);
        stopattacksound();
        lastnode = -1;
    }

    int Player::respawnwait(int secs, int delay)
    {
        return std::max(0, secs - (_engine->lastmillis - lastpain - delay)/1000);
    }

}