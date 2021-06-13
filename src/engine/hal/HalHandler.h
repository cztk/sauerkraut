//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_HALHANDLER_H
#define SAUERKRAUT_HALHANDLER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include "../state.h"
#include "../../config/Config.h"

#include "iVideo.h"
#include "iSound.h"

#include "video/Sdl2VideoHandler.h"
#include "sound/Sdl2SoundHandler.h"




namespace kraut::engine::hal {

    class HalHandler {
    public:
        iVideo *videoHandler = nullptr;
        iSound *soundHandler = nullptr;

        explicit HalHandler(kraut::engine::State *pState, kraut::config::Config *pConfig,
                            kraut::log::LogHandler *pHandler);

        ~HalHandler();
        std::thread run();
        void stop();
        bool initialize();

        bool initVideo();

    private:
        State *_state;
        config::Config *_config;
        log::LogHandler *_logHandler;


        std::mutex _main_mutex;
        std::condition_variable _cv;
        bool _stop = false;
        bool _process = false;

        void deinitialize();
        void thread_main();


        bool initSound();
    };

}

#endif //SAUERKRAUT_HALHANDLER_H
