//
// Created by ztk on 2021-06-14.
//

#ifndef SAUERKRAUT_IRENDERER_H
#define SAUERKRAUT_IRENDERER_H

namespace kraut::engine::hal::video::sdl::renderer {

    class iRenderer {

    public:
        virtual bool checkextensions() = 0;
        virtual bool init() = 0;
        virtual void setuptexcompress(int texcompressslevel) = 0;
        virtual void resizeViewport(int width, int height, int x, int y) = 0;
    };

}

#endif //SAUERKRAUT_IRENDERER_H
