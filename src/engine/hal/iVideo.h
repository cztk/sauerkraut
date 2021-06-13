//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_IVIDEO_H
#define SAUERKRAUT_IVIDEO_H

namespace kraut::engine::hal {
    class iVideo {
    public:
        virtual bool init() = 0;

        virtual void deinit() = 0;

        virtual ~iVideo() = default;

        virtual void grab_keyboard(bool b) = 0;

        virtual void minimize_on_focus_loss(bool b) = 0;

        virtual bool setupScreen() = 0;
    };
}
#endif //SAUERKRAUT_IVIDEO_H
