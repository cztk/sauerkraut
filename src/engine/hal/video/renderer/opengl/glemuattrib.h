//
// Created by ztk on 2021-06-15.
//

#ifndef SAUERKRAUT_GLEMUATTRIB_H
#define SAUERKRAUT_GLEMUATTRIB_H
namespace kraut::engine::hal::video::sdl::renderer::opengl {
    struct glemu_attribinfo
    {
        int type, size, formatsize, offset;
        GLenum format;

        glemu_attribinfo() : type(0), size(0), formatsize(0), offset(0), format(GL_FALSE) {}

        bool operator==(const glemu_attribinfo &a) const
        {
            return type == a.type && size == a.size && format == a.format && offset == a.offset;
        }
        bool operator!=(const glemu_attribinfo &a) const
        {
            return type != a.type || size != a.size || format != a.format || offset != a.offset;
        }
    };

    enum {
        ATTRIB_VERTEX = 0,
        ATTRIB_COLOR = 1,
        ATTRIB_TEXCOORD0 = 2,
        ATTRIB_TEXCOORD1 = 3,
        ATTRIB_NORMAL = 4,
        ATTRIB_TANGENT = 5,
        ATTRIB_BONEWEIGHT = 6,
        ATTRIB_BONEINDEX = 7,
        GLEMU_MAXATTRIBS = 8
    };
}
#endif //SAUERKRAUT_GLEMUATTRIB_H
