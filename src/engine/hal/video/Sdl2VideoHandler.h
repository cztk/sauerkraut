//
// Created by ztk on 2021-06-11.
// TDO https://www.glfw.org/
// https://github.com/nigels-com/glew
//

#ifndef SAUERKRAUT_SDL2SOUNDHANDLER_H
#define SAUERKRAUT_SDL2HANDLER_H

#include <string>
#include <SDL2/SDL.h>
#include "../../../utils/stringhelper.h"
#include "../iVideo.h"
#include "../../state.h"
#include "../../../log/LogHandler.h"
#include "../../../config/Config.h"
#include "iHardwareAccel.h"
#include "hardwareaccel/Opengl.h"

namespace kraut::engine::hal::video::sdl {
    class Sdl2VideoHandler final : public iVideo {
    public:
        explicit Sdl2VideoHandler(log::LogHandler *pLogHandler, kraut::config::Config *pConfig);

        bool init() final;

        void deinit() final;

        void grab_keyboard(bool b) final;

        void minimize_on_focus_loss(bool b) final;

        bool setupScreen() final;
        void showcursor(bool b) final;
        void textinput(bool b) final;
        bool setupHardwareAccel() final;

    private:
        log::LogHandler *_logHandler;
        config::Config *_config;

        SDL_version version{};
        SDL_Window *screen = nullptr;
        SDL_GLContext glcontext = nullptr;

        SDL_Rect desktop;

        int desktopw = 0;
        int desktoph = 0;

        int winx = SDL_WINDOWPOS_UNDEFINED;
        int winy = SDL_WINDOWPOS_UNDEFINED;
        int winw = 0;
        int winh = 0;
        int screen_wflags;

        bool initwindowpos = false;

        int multisample_config = 0;
        const std::vector<int> multisample_configs{
                0x3, /* try everything */
                0x2, 0x1, /* try disabling one at a time */
                0 /* try disabling everything */
        };

#ifdef __APPLE__
        const std::vector<int> glversions{ 32, 20 };
#else
        const std::vector<int> glversions{33, 32, 31, 30, 20};
#endif


        int sdl_xgrab_bug = 0;
        int glcompat;

        hardwareaccel::iHardwareAccel *hardwareAccel;

    };
}

#endif //SAUERKRAUT_SDL2SOUNDHANDLER_H
