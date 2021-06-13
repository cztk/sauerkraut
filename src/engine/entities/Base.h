//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_BASE_H
#define SAUERKRAUT_BASE_H

#include <eigen3/Eigen/Core>

namespace kraut::engine::entities {
    class Base {
    public:
        Eigen::Vector3d o;                                      // position
        short attr1, attr2, attr3, attr4, attr5;
        unsigned char type;                                 // type is one of the above
        unsigned char reserved;
    };
}

#endif //SAUERKRAUT_BASE_H
