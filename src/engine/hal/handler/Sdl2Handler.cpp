//
// Created by ztk on 2021-06-11.
//

#include "Sdl2Handler.h"


namespace kraut::engine::hal::sdl {

    bool Sdl2Handler::init() {
        if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0) {
            last_error =  utils::StringHelper::vFormat("Unable to initialize SDL: %s", SDL_GetError());
            return false;
        }
#ifdef SDL_VIDEO_DRIVER_X11
        SDL_version version;
        SDL_GetVersion(&version);
        if (SDL_VERSIONNUM(version.major, version.minor, version.patch) <= SDL_VERSIONNUM(2, 0, 12))
            sdl_xgrab_bug = 1;
#endif
        return true;
    }

    void Sdl2Handler::deinit() {

    }

    Sdl2Handler::Sdl2Handler() = default;
}