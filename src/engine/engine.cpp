//
// Created by ztk on 2021-06-11.
//

#include "engine.h"

namespace kraut::engine {

    Engine::Engine(State *pState, config::Config *pConfig, log::LogHandler *pLogHandler) : _state(pState),
                                                                                           _config(pConfig),
                                                                                           _logHandler(pLogHandler) {

    }

    Engine::~Engine() = default;

    bool Engine::initialize() {
        _state->initing = kraut::engine::INITING;

        if (_config->dedicated <= 1) {
            _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal"));
            engine_hal_hnd = new kraut::engine::hal::HalHandler(_state, _config, _logHandler);
            engine_hal_thread = engine_hal_hnd->run();
        }

        networkHandler = new network::NetworkHandler(_logHandler);
        networkHandler->initialize();

        return true;
    }

    bool Engine::initSound() {
        return engine_hal_hnd->initSound();
    }

    bool Engine::initVideo() {
        if(engine_hal_hnd->initVideo()) {
            if(!_config->engine.usetexcompress) _config->engine.texcompressquality = -1;
            engine_hal_hnd->videoHandler->setuptexcompress(_config->engine.texcompressquality);
            engine_hal_hnd->videoHandler->resizeViewport(_config->engine.screen_w, _config->engine.screen_h, 0, 0);
            engine_hal_hnd->videoHandler->showcursor(false);
            engine_hal_hnd->videoHandler->textinput(false);
        }
        return false;
    }

    void Engine::deinitialize() {
        if (_config->dedicated <= 1 && engine_hal_hnd != nullptr) {
            engine_hal_hnd->stop();
            if (engine_hal_thread.joinable()) {
                engine_hal_thread.join();
            }
            delete engine_hal_hnd;
        }

        networkHandler->deinitialize();
        delete networkHandler;
    }
}