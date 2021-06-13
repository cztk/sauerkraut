//
// Created by ztk on 2021-06-13.
//

#include "GameData.h"
namespace kraut::game {

    Weapon *GameData::getWeapon(int n) {
        // TODO oh oh oh ah ah ah but ok ;)
        return weapons[n];
    }

    int GameData::addWeapon(Weapon *pWeapon) {
        return 0;
    }
}