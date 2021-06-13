//
// Created by ztk on 2021-06-13.
//

#include "PlayerState.h"

namespace kraut::game {

    PlayerState::PlayerState() : maxhealth(100), aitype(AI_NONE), skill(0) {

    }

    void PlayerState::baseammo(int gun, int k, int scale) {
        ammo[gun] = (itemstats[gun - GUN_SG].add * k) / scale;
    }

    void PlayerState::addammo(int gun, int k, int scale) {
        itemstat &is = itemstats[gun - GUN_SG];
        ammo[gun] = std::min(ammo[gun] + (is.add * k) / scale, is.max);
    }

    bool PlayerState::hasmaxammo(int type) {
        const itemstat &is = itemstats[type - engine::entities::I_SHELLS];
        return ammo[type - engine::entities::I_SHELLS + GUN_SG] >= is.max;
    }

    bool PlayerState::canpickup(int type) {
        if (type < engine::entities::I_SHELLS || type > engine::entities::I_QUAD) return false;
        itemstat &is = itemstats[type - engine::entities::I_SHELLS];
        switch (type) {
            case engine::entities::I_BOOST:
                return maxhealth < is.max || health < maxhealth;
            case engine::entities::I_HEALTH:
                return health < maxhealth;
            case engine::entities::I_GREENARMOUR:
                // (100h/100g only absorbs 200 damage)
                if (armourtype == engine::entities::A_YELLOW && armour >= 100) return false;
            case engine::entities::I_YELLOWARMOUR:
                return !armourtype || armour < is.max;
            case engine::entities::I_QUAD:
                return quadmillis < is.max;
            default:
                return ammo[is.info] < is.max;
        }
    }

    void PlayerState::pickup(int type) {
        if (type < engine::entities::I_SHELLS || type > engine::entities::I_QUAD) return;
        itemstat &is = itemstats[type - engine::entities::I_SHELLS];
        switch (type) {
            case engine::entities::I_BOOST:
                maxhealth = std::min(maxhealth + is.info, is.max);
            case engine::entities::I_HEALTH: // boost also adds to health
                health = std::min(health + is.add, maxhealth);
                break;
            case engine::entities::I_GREENARMOUR:
            case engine::entities::I_YELLOWARMOUR:
                armour = std::min(armour + is.add, is.max);
                armourtype = is.info;
                break;
            case engine::entities::I_QUAD:
                quadmillis = std::min(quadmillis + is.add, is.max);
                break;
            default:
                ammo[is.info] = std::min(ammo[is.info] + is.add, is.max);
                break;
        }
    }

    void PlayerState::respawn() {
        maxhealth = 100;
        health = maxhealth;
        armour = 0;
        armourtype = engine::entities::A_BLUE;
        quadmillis = 0;
        gunselect = GUN_PISTOL;
        gunwait = 0;
        for (int i = 0; i < NUMGUNS; i++)
            ammo[i] = 0;
        ammo[GUN_FIST] = 1;
    }

    void PlayerState::spawnstate(int gamemode) {
        if (m_demo) {
            gunselect = GUN_FIST;
        } else if (m_insta) {
            armour = 0;
            health = 1;
            gunselect = GUN_RIFLE;
            ammo[GUN_RIFLE] = 100;
        } else if (m_regencapture) {
            //TODO add option, figure this is server or game code
            //if (regenbluearmour) {
            if (true) {
                armourtype = engine::entities::A_BLUE;
                armour = 25;
            }
            gunselect = GUN_PISTOL;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
        } else if (m_tactics) {
            armourtype = engine::entities::A_GREEN;
            armour = 100;
            ammo[GUN_PISTOL] = 40;
            //TODO add random
            //int spawngun1 = rnd(5) + 1, spawngun2;
            int spawngun1 = 4, spawngun2;
            gunselect = spawngun1;
            baseammo(spawngun1, m_noitems ? 2 : 1);
            do {
                // todo random
                //spawngun2 = utils::rnd(5) + 1;
                spawngun2 = 2 + 1;
            }while (spawngun1 == spawngun2);
            baseammo(spawngun2, m_noitems ? 2 : 1);
            if (m_noitems) ammo[GUN_GL] += 1;
        } else if (m_efficiency) {
            armourtype = engine::entities::A_GREEN;
            armour = 100;
            for (int i = 0; i < 5; i++)
                baseammo(i + 1);
            gunselect = GUN_CG;
            ammo[GUN_CG] /= 2;
        } else if (m_ctf || m_collect) {
            armourtype = engine::entities::A_BLUE;
            armour = 50;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
        } else if (m_sp) {
            if (m_dmsp) {
                armourtype = engine::entities::A_BLUE;
                armour = 25;
            }
            ammo[GUN_PISTOL] = 80;
            ammo[GUN_GL] = 1;
        } else {
            armourtype = engine::entities::A_BLUE;
            armour = 25;
            ammo[GUN_PISTOL] = 40;
            ammo[GUN_GL] = 1;
        }
    }

    // just subtract damage here, can set death, etc. later in code calling this
    int PlayerState::dodamage(int damage) {
        int ad = (damage * (armourtype + 1) * 25) / 100; // let armour absorb when possible
        if (ad > armour) ad = armour;
        armour -= ad;
        damage -= ad;
        health -= damage;
        return damage;
    }

    int PlayerState::hasammo(int gun, int exclude) {
        return gun >= 0 && gun <= NUMGUNS && gun != exclude && ammo[gun] > 0;
    }
}