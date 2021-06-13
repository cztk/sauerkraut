//
// Created by ztk on 2021-06-12.
//

#include "Sdl2SoundHandler.h"

namespace kraut::engine::hal::sound::sdl {

    Sdl2SoundHandler::Sdl2SoundHandler(log::LogHandler *pLogHandler, kraut::config::Config *pConfig) : _logHandler(
            pLogHandler),
                                                                                                       _config(pConfig) {

    }

    Sdl2SoundHandler::~Sdl2SoundHandler() {

    }

    bool Sdl2SoundHandler::init() {
        return false;
    }

    void Sdl2SoundHandler::deinit() {

    }

    void Sdl2SoundHandler::stopsound(int n, int chanid, int fade) {

    }


}