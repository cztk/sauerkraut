//
// Created by ztk on 2021-06-11.
//

#include "engine.h"

namespace kraut::engine {

        Engine::Engine(State *pState, config::Config *pConfig, log::LogHandler *pLogHandler) : _state(pState), _config(pConfig), _logHandler(pLogHandler) {

        }

        Engine::~Engine() = default;

        bool Engine::initialize() {
            if (_config->dedicated <= 1) {
                _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal"));
                engine_hal_hnd = new kraut::engine::hal::HalHandler(_state, _config, _logHandler);
                engine_hal_thread = engine_hal_hnd->run();
            }
            return true;
        }

        void Engine::deinitialize() {
            if (_config->dedicated <= 1 && engine_hal_hnd != nullptr) {
                engine_hal_hnd->stop();
                if(engine_hal_thread.joinable()) {
                    engine_hal_thread.join();
                }
                delete engine_hal_hnd;
            }
        }
}