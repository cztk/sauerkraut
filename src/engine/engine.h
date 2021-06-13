//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_ENGINE_H
#define SAUERKRAUT_ENGINE_H

#include "state.h"
#include "../config/Config.h"
#include "hal/HalHandler.h"
#include "../network/NetworkHandler.h"

namespace kraut::engine {

    class Engine {
    public:
        Engine(State *pState, config::Config *pConfig, log::LogHandler *pLogHandler);
        ~Engine();

        bool initialize();
        void deinitialize();

        int curtime = 0, lastmillis = 1, elapsedtime = 0, totalmillis = 1;

        kraut::engine::hal::HalHandler *engine_hal_hnd = nullptr;
    private:
        State *_state;
        config::Config *_config;
        log::LogHandler *_logHandler;

        network::NetworkHandler *networkHandler;


        std::thread engine_hal_thread;


    };
}
#endif //SAUERKRAUT_ENGINE_H
