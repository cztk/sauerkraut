//
// Created by ztk on 2021-06-13.
//

#include "Phys.h"

namespace kraut::engine::entities {

    Phys::Phys() : o(0, 0, 0), deltapos(0, 0, 0), newpos(0, 0, 0), yaw(0), pitch(0), roll(0), maxspeed(100),
                radius(4.1f), eyeheight(14), aboveeye(1), xradius(4.1f), yradius(4.1f), zmargin(0),
                state(CS_ALIVE), editstate(CS_ALIVE), type(ENT_PLAYER),
                collidetype(COLLIDE_ELLIPSE),
                blocked(false)
    {
        reset();
    }

    void Phys::resetinterp()
    {
        newpos = o;
        deltapos = Eigen::Vector3d(0, 0, 0);
    }

    void Phys::reset()
    {
        inwater = 0;
        timeinair = 0;
        jumping = false;
        strafe = move = 0;
        physstate = PHYS_FALL;
        vel = falling = Eigen::Vector3d(0, 0, 0);
        floor = Eigen::Vector3d(0, 0, 1);
    }

    Eigen::Vector3d Phys::feetpos(float offset) const {
        return Eigen::Vector3d(o) + Eigen::Vector3d(0, 0, offset - eyeheight);
    }
    Eigen::Vector3d Phys::headpos(float offset) const {
        return Eigen::Vector3d(o) + Eigen::Vector3d(0, 0, offset);
    }

    bool Phys::maymove() const {
        return timeinair || physstate < PHYS_FLOOR || vel.dot(vel) > 1e-4f || deltapos.dot(deltapos) > 1e-4f;
    }
}