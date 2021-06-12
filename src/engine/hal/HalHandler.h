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
#include "handler/Sdl2Handler.h"
#include "iHandler.h"

namespace kraut::engine::hal {

    class HalHandler {
    public:
        explicit HalHandler(kraut::engine::State *pState, kraut::config::Config *pConfig,
                            kraut::log::LogHandler *pHandler);

        ~HalHandler();
        std::thread run();
        void stop();
        bool initialize();

        void initVideo();

    private:
        State *_state;
        config::Config *_config;
        log::LogHandler *_logHandler;

        iHandler *hardwareHandler = nullptr;


        std::mutex _main_mutex;
        std::condition_variable _cv;
        bool _stop = false;
        bool _process = false;

        void deinitialize();
        void thread_main();


    };

}

#endif //SAUERKRAUT_HALHANDLER_H
