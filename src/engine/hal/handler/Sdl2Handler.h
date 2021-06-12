//
// Created by ztk on 2021-06-11.
//

#ifndef SAUERKRAUT_SDL2HANDLER_H
#define SAUERKRAUT_SDL2HANDLER_H

#include <string>
#include <SDL2/SDL.h>
#include "../../../utils/stringhelper.h"
#include "../iHandler.h"
#include "../../state.h"
#include "../../../log/LogHandler.h"

namespace kraut::engine::hal::sdl {
    class Sdl2Handler : public iHandler {
    public:
        explicit Sdl2Handler(log::LogHandler *pLogHandler);
        bool init() override;
        void deinit() override;
    private:
        int sdl_xgrab_bug = 0;
        log::LogHandler *_logHandler;
    };
}

#endif //SAUERKRAUT_SDL2HANDLER_H
