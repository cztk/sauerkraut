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

        if (initialize()) {

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

    bool HalHandler::initVideo() {
        _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal:video"));
        videoHandler = new video::sdl::Sdl2VideoHandler(_logHandler, _config);
        if(videoHandler->init()) {
            videoHandler->grab_keyboard(false);
#if !defined(WIN32) && !defined(__APPLE__)
            videoHandler->minimize_on_focus_loss(false);
#endif
            return videoHandler->setupScreen();
        } else {
            return false;
        }
    }

    bool HalHandler::initSound() {
        _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal:sound"));
        soundHandler = new sound::sdl::Sdl2SoundHandler(_logHandler, _config);
        return soundHandler->init();
        return false;
    }

    void HalHandler::deinitialize() {

        if (videoHandler != nullptr) {
            videoHandler->deinit();
        }

    }

    bool HalHandler::initialize() {
        return false;
    }


}