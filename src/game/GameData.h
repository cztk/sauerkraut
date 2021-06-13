//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_GAMEDATA_H
#define SAUERKRAUT_GAMEDATA_H

#include <vector>
#include "Weapon.h"

namespace kraut::game {
    class GameData {
    public:
        int addWeapon(Weapon *pWeapon);
        Weapon *getWeapon(int n);
    private:
        std::vector<Weapon *> weapons;
    };
}

#endif //SAUERKRAUT_GAMEDATA_H
