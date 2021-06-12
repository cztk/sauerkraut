//
// Created by ztk on 2021-06-11.
//

#include "HalHandler.h"

namespace kraut::engine::hal {

    HalHandler::HalHandler(kraut::engine::State *pState, kraut::config::Config *pConfig,
                           kraut::log::LogHandler *pHandler) : _state(pState), _config(pConfig), _logHandler(pHandler) {

    }

    HalHandler::~HalHandler() = default;

    std::thread HalHandler::run() {
        return std::thread([this] { this->thread_main(); });
    }

    void HalHandler::thread_main() {

        if(initialize()) {

            while (!_stop) {
                std::unique_lock<std::mutex> lk(_main_mutex);
                _cv.wait(lk, [this] { return _process || _stop; });


                _process = false;
                lk.unlock();
            }

        }

        deinitialize();
    }

    void HalHandler::stop() {
        {
            _stop = true;
            _cv.notify_one();
        }
    }

    void HalHandler::initVideo() {
        _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal:video"));

        hardwareHandler->grab_keyboard(false);
#if !defined(WIN32) && !defined(__APPLE__)
        hardwareHandler->minimize_on_focus_loss(false);
#endif
        hardwareHandler->setupScreen();
    }


    bool HalHandler::initialize() {
        hardwareHandler = new sdl::Sdl2Handler(_logHandler, _config);
        return hardwareHandler->init();
    }

    void HalHandler::deinitialize() {

        if(hardwareHandler != nullptr) {
            hardwareHandler->deinit();
        }

    }
}