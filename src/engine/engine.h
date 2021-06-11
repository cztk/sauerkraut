//
// Created by ztk on 2021-06-09.
//

#ifndef SAUERKRAUT_ENGINE_H
#define SAUERKRAUT_ENGINE_H

#include "state.h"
#include "../config/Config.h"
#include "hal/HalHandler.h"

namespace kraut::engine {

    class Engine {
    public:
        Engine(State *pState, config::Config *pConfig, log::LogHandler *pLogHandler);
        ~Engine();

        bool initialize();
    private:
        State *_state;
        config::Config *_config;
        log::LogHandler *_logHandler;

        kraut::engine::hal::HalHandler *engine_hal_hnd = nullptr;
        std::thread engine_hal_thread;

        void deinitialize();
    };
}
#endif //SAUERKRAUT_ENGINE_H
