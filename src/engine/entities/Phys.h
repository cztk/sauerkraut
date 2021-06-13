//
// Created by ztk on 2021-06-13.
//

#ifndef SAUERKRAUT_PHYS_H
#define SAUERKRAUT_PHYS_H

#include <eigen3/Eigen/Core>
#include "States.h"

namespace kraut::engine::entities {

    // physent
    class Phys {
    public:

        Eigen::Vector3d o, vel, falling;                        // origin, velocity
        Eigen::Vector3d deltapos, newpos;                       // movement interpolation
        float yaw, pitch, roll;
        float maxspeed;                             // cubes per second, 100 for player
        float radius, eyeheight, aboveeye;          // bounding box size
        float xradius, yradius, zmargin;
        Eigen::Vector3d floor;                                  // the normal of floor the dynent is on

        ushort timeinair;
        unsigned char inwater;
        bool jumping;
        char move, strafe;

        unsigned char physstate;                            // one of PHYS_* above
        unsigned char state, editstate;                     // one of CS_* above
        unsigned char type;                                 // one of ENT_* above
        unsigned char collidetype;                          // one of COLLIDE_* above

        bool blocked; // used by physics to signal ai

        Phys();

        [[nodiscard]] Eigen::Vector3d feetpos(float offset = 0) const;

        [[nodiscard]] Eigen::Vector3d headpos(float offset = 0) const;

        [[nodiscard]] bool maymove() const;

        virtual void reset();

        void resetinterp();
    };

}

#endif //SAUERKRAUT_PHYS_H
