//
// Created by ztk on 2021-06-14.
//

#ifndef SAUERKRAUT_IHARDWAREACCEL_H
#define SAUERKRAUT_IHARDWAREACCEL_H

namespace kraut::engine::hal::video::sdl::hardwareaccel {

    class iHardwareAccel {

    public:
        virtual bool checkextensions() = 0;
        virtual bool init() = 0;
    };

}

#endif //SAUERKRAUT_IHARDWAREACCEL_H
