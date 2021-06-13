//
// Created by ztk on 2021-06-12.
//

#ifndef SAUERKRAUT_SDL2SOUNDHANDLER_H
#define SAUERKRAUT_SDL2SOUNDHANDLER_H

#include <SDL2/SDL.h>

#include "../../../log/LogHandler.h"
#include "../../../config/Config.h"
#include "../iSound.h"

namespace kraut::engine::hal::sound::sdl {

    class Sdl2SoundHandler final : public iSound {
    public:
        explicit Sdl2SoundHandler(log::LogHandler *pLogHandler, kraut::config::Config *pConfig);
        ~Sdl2SoundHandler() final;

        bool init() final;
        void deinit() final;

        void stopsound(int n, int chanid, int fade) final;
    private:
        log::LogHandler *_logHandler;
        config::Config *_config;

        SDL_version version{};
        bool nosound = true;


    };

}
#endif //SAUERKRAUT_SDL2SOUNDHANDLER_H
