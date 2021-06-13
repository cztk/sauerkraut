//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_ISOUND_H
#define SAUERKRAUT_ISOUND_H

namespace kraut::engine::hal {
    class iSound {
    public:
        virtual bool init() = 0;

        virtual void deinit() = 0;

        virtual ~iSound() = default;

        virtual void stopsound(int n, int chanid, int fade) = 0;

    };
}
#endif //SAUERKRAUT_ISOUND_H
