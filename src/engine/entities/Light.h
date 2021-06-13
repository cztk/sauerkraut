//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_LIGHT_H
#define SAUERKRAUT_LIGHT_H

#include <eigen3/Eigen/Core>

namespace kraut::engine::entities {
    class Light {
    public:
        Eigen::Vector3d color, dir;
        int millis;

        Light();
    };
}

#endif //SAUERKRAUT_LIGHT_H
