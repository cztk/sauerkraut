//
// Created by ztk on 2021-06-11.
//

#include "Sdl2VideoHandler.h"


namespace kraut::engine::hal::video::sdl {

    bool Sdl2VideoHandler::init() {
        _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal:sdl"));
        if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            _logHandler->log(kraut::log::LogLevel::Critical,
                             utils::StringHelper::vFormat("hal:sdl: Unable to initialize SDL: %s", SDL_GetError()));
            return false;
        }
#ifdef SDL_VIDEO_DRIVER_X11

        SDL_GetVersion(&version);
        if (SDL_VERSIONNUM(version.major, version.minor, version.patch) <= SDL_VERSIONNUM(2, 0, 12)) {
            sdl_xgrab_bug = 1;
#ifdef KRAUT_LOG_DEBUG
            _logHandler->log(kraut::log::LogLevel::Debug, utils::StringHelper::vFormat("hal:sdl: has sdl_xgrab_bug"));
#endif
        }
#endif
        return true;
    }

    void Sdl2VideoHandler::deinit() {
        if(renderer) {
            //TODO
            //renderer->deinit();
            delete renderer;
        }

    }

    void Sdl2VideoHandler::grab_keyboard(bool b) {
        if (b) {
            SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");
        } else {
            SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "0");
        }
    }

    void Sdl2VideoHandler::minimize_on_focus_loss(bool b) {
        if (b) {
            SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "1");
        } else {
            SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
        }
    }


    Sdl2VideoHandler::Sdl2VideoHandler(log::LogHandler *pLogHandler, kraut::config::Config *pConfig, engine::Engine *pEngine) :
    _logHandler(pLogHandler), _config(pConfig), _engine(pEngine) {

    }

    // TODO make this nice
    bool Sdl2VideoHandler::setupScreen() {
        if (glcontext) {
            SDL_GL_DeleteContext(glcontext);
            glcontext = nullptr;
        }
        if (screen) {
            SDL_DestroyWindow(screen);
            screen = nullptr;
        }

        //curvsync = -1; ?


        if (SDL_GetDisplayBounds(0, &desktop) < 0) {
            _logHandler->log(kraut::log::LogLevel::Critical,
                             utils::StringHelper::vFormat("hal:sdl: failed querying desktop bounds: %s",
                                                          SDL_GetError()));
            return false;
        }
        desktopw = desktop.w;
        desktoph = desktop.h;

        if (_config->engine.screen_h < 0)
            _config->engine.screen_h = _config->engine.screen_fullscreen ? desktoph : SCREEN_DEFAULTH;
        if (_config->engine.screen_w < 0) _config->engine.screen_w = (_config->engine.screen_h * desktopw) / desktoph;
        _config->engine.screen_w = std::clamp(_config->engine.screen_w, SCREEN_MINW, SCREEN_MAXW);
        _config->engine.screen_h = std::clamp(_config->engine.screen_h, SCREEN_MINH, SCREEN_MAXH);

        if (_config->engine.screen_fulldesktop) {
            _config->engine.screen_w = std::min(_config->engine.screen_w, desktopw);
            _config->engine.screen_h = std::min(_config->engine.screen_h, desktoph);
        }

        winx = SDL_WINDOWPOS_UNDEFINED;
        winy = SDL_WINDOWPOS_UNDEFINED;
        winw = _config->engine.screen_w;
        winh = _config->engine.screen_h;
        screen_wflags = SDL_WINDOW_RESIZABLE;
        if (_config->engine.screen_fullscreen) {
            if (_config->engine.screen_fulldesktop) {
                winw = desktopw;
                winh = desktoph;
                screen_wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            } else screen_wflags |= SDL_WINDOW_FULLSCREEN;
            initwindowpos = true;
        }

        SDL_GL_ResetAttributes();
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#if !defined(WIN32) && !defined(__APPLE__)
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
#endif


        if (!_config->engine.screen_depthbits)
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        if (!_config->engine.screen_fsaa) {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
        }

        for (auto const &config: multisample_configs) {
            multisample_config = config;

            if (!_config->engine.screen_depthbits && config & 1) continue;
            if (_config->engine.screen_fsaa <= 0 && config & 2) continue;
            if (_config->engine.screen_depthbits)
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,
                                    config & 1 ? _config->engine.screen_depthbits
                                               : 24);
            if (_config->engine.screen_fsaa > 0) {
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, config & 2 ? 1 : 0);
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, config & 2 ? _config->engine.screen_fsaa : 0);
            }
            screen = SDL_CreateWindow("Cube 2: Sauerkraut", winx, winy, winw, winh,
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS |
                                      SDL_WINDOW_MOUSE_FOCUS | screen_wflags);
            if (!screen) continue;


            for (auto const &glversion: glversions) {
                glcompat = glversion <= 30 ? 1 : 0;
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glversion / 10);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glversion % 10);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, glversion >= 32 ? SDL_GL_CONTEXT_PROFILE_CORE : 0);
                glcontext = SDL_GL_CreateContext(screen);
                if (glcontext) break;
            }
            if (glcontext) break;
        }


        if (!screen) {
            _logHandler->log(kraut::log::LogLevel::Critical,
                             utils::StringHelper::vFormat("hal:sdl: failed to create OpenGL window: %s",
                                                          SDL_GetError()));
            return false;
        } else if (!glcontext) {
            _logHandler->log(kraut::log::LogLevel::Critical,
                             utils::StringHelper::vFormat("hal:sdl: failed to create OpenGL context: %s",
                                                          SDL_GetError()));
            return false;
        } else {
            if (_config->engine.screen_depthbits && (multisample_config & 1) == 0) {
                // TODO game console log
                _logHandler->log(kraut::log::LogLevel::Info,
                                 utils::StringHelper::vFormat("hal:sdl: %d bit z-buffer not supported - disabling",
                                                              _config->engine.screen_depthbits));
                //conoutf(CON_WARN, "%d bit z-buffer not supported - disabling", depthbits);
            }
            if (_config->engine.screen_fsaa > 0 && (multisample_config & 2) == 0) {
                // TODO game console log
                //conoutf(CON_WARN, "%dx anti-aliasing not supported - disabling", fsaa);
                _logHandler->log(kraut::log::LogLevel::Info,
                                 utils::StringHelper::vFormat("hal:sdl: %dx anti-aliasing not supported - disabling",
                                                              _config->engine.screen_fsaa));
            }
        }

        SDL_SetWindowMinimumSize(screen, SCREEN_MINW, SCREEN_MINH);
        SDL_SetWindowMaximumSize(screen, SCREEN_MAXW, SCREEN_MAXH);

        SDL_GetWindowSize(screen, &_config->engine.screen_w, &_config->engine.screen_h);
        return true;
    }


    void Sdl2VideoHandler::showcursor(bool b) {
        if(b) {
            SDL_ShowCursor(SDL_TRUE);
        } else {
            SDL_ShowCursor(SDL_FALSE);
        }
    }

    void Sdl2VideoHandler::textinput(bool b) {
        if(b) {
            SDL_StartTextInput();
        } else {
            SDL_StopTextInput();
        }
    }

    bool Sdl2VideoHandler::setupHardwareAccel() {
        _logHandler->log(kraut::log::LogLevel::Info, utils::StringHelper::vFormat("init: hal:sdl::gl"));
        renderer = new renderer::Opengl(_engine);
        return renderer->init();
    }

    void Sdl2VideoHandler::setuptexcompress(int texcompressslevel) {
        if(renderer) {
            renderer->setuptexcompress(texcompressslevel);
        }

    }
    void Sdl2VideoHandler::resizeViewport(int width, int height, int x, int y) {
        if(renderer) {
            renderer->resizeViewport(width, height, x, y);
        }
    }

}