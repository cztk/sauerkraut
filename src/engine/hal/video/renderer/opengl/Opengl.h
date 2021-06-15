//
// Created by ztk on 2021-06-14.
//

#ifndef SAUERKRAUT_OPENGL_H
#define SAUERKRAUT_OPENGL_H

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <string>
#include "../../../../../utils/stringhelper.h"
#include "../../iRenderer.h"
#include "glemuattrib.h"
#include "glexts.h"
#include "../../../../../log/LogHandler.h"

namespace kraut::engine::hal::video::sdl::renderer::opengl {
    class Opengl final : public iRenderer {
    public:
        explicit Opengl(log::LogHandler *pLoghandler);
        bool checkextensions() override;
        bool init() final;
        void setuptexcompress(int texcompressslevel) final;
        void resizeViewport(int width, int height, int x, int y) final;

    private:

        log::LogHandler *_logHandler;
        int fpdepthfx = 0;
        int reservevpparams = 10;
        int hwmaxaniso = 0;

        int usetexcompress = 0;
        int texcompress = 0;

        int waterfallrefract = 0;
        int grass = 0;
        int glare = 0;
        int depthfxsize = 0;
        int blurdepthfx = 0;
        int filltjoints = 0;
        int smoothshadowmappeel =0;
        int maxdynlights = 5; //TODO adjustable

        int glversion = 0;
        int glslversion = 0;
        int glcompat = 0;
        int hwtexsize = 0;
        int hwcubetexsize = 0;
        int dbgexts = 0;
        int shadowmap = 1;
        int minimizetcusage = 0;

        int ati_skybox_bug = 0;
        int ati_minmax_bug= 0;
        int ati_cubemap_bug= 0;
        int intel_vertexarray_bug= 0;
        int intel_mapbufferrange_bug= 0;
        int mesa_swap_bug= 0;
        int useubo= 1;
        int rtscissor= 1;
        int blurtile= 1;
        int rtsharefb= 1;

        bool hasVAO = false, hasFBO = false, hasAFBO = false, hasDS = false, hasTF = false, hasTRG = false, hasTSW = false, hasS3TC = false, hasFXT1 = false, hasLATC = false, hasRGTC = false, hasAF = false, hasFBB = false, hasUBO = false, hasMBR = false;

        std::unordered_set<std::string> glexts;

        void *getprocaddress(const char *name);
        void parseglexts();

        bool hasext(const char *ext);

#ifndef __APPLE__
        PFNGLGETSTRINGIPROC           glGetStringi_;
        PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays_;
        PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements_;
        PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate_;
        PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate_;
        PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate_;
        PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate_;
        PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate_;
        PFNGLGENBUFFERSPROC glGenBuffers_;
        PFNGLBINDBUFFERPROC glBindBuffer_;
        PFNGLMAPBUFFERPROC glMapBuffer_;
        PFNGLUNMAPBUFFERPROC glUnmapBuffer_;
        PFNGLBUFFERDATAPROC glBufferData_;
        PFNGLBUFFERSUBDATAPROC glBufferSubData_;
        PFNGLDELETEBUFFERSPROC glDeleteBuffers_;
        PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData_;
        PFNGLGETQUERYIVPROC glGetQueryiv_;
        PFNGLGENQUERIESPROC glGenQueries_;
        PFNGLDELETEQUERIESPROC glDeleteQueries_;
        PFNGLBEGINQUERYPROC glBeginQuery_;
        PFNGLENDQUERYPROC glEndQuery_;
        PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv_;
        PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv_;
        PFNGLCREATEPROGRAMPROC glCreateProgram_;
        PFNGLDELETEPROGRAMPROC glDeleteProgram_;
        PFNGLUSEPROGRAMPROC glUseProgram_;
        PFNGLCREATESHADERPROC glCreateShader_;
        PFNGLDELETESHADERPROC glDeleteShader_;
        PFNGLSHADERSOURCEPROC glShaderSource_;
        PFNGLCOMPILESHADERPROC glCompileShader_;
        PFNGLGETSHADERIVPROC glGetShaderiv_;
        PFNGLGETPROGRAMIVPROC glGetProgramiv_;
        PFNGLATTACHSHADERPROC glAttachShader_;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_;
        PFNGLLINKPROGRAMPROC glLinkProgram_;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_;
        PFNGLUNIFORM1FPROC glUniform1f_;
        PFNGLUNIFORM2FPROC glUniform2f_;
        PFNGLUNIFORM3FPROC glUniform3f_;
        PFNGLUNIFORM4FPROC glUniform4f_;
        PFNGLUNIFORM1FVPROC glUniform1fv_;
        PFNGLUNIFORM2FVPROC glUniform2fv_;
        PFNGLUNIFORM3FVPROC glUniform3fv_;
        PFNGLUNIFORM4FVPROC glUniform4fv_;
        PFNGLUNIFORM1IPROC glUniform1i_;
        PFNGLUNIFORM2IPROC glUniform2i_;
        PFNGLUNIFORM3IPROC glUniform3i_;
        PFNGLUNIFORM4IPROC glUniform4i_;
        PFNGLUNIFORM1IVPROC glUniform1iv_;
        PFNGLUNIFORM2IVPROC glUniform2iv_;
        PFNGLUNIFORM3IVPROC glUniform3iv_;
        PFNGLUNIFORM4IVPROC glUniform4iv_;


        PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv_;
        PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv_;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_;
        PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation_;
        PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform_;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_;
        PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray_;
        PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f_;
        PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv_;
        PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s_;
        PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv_;
        PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f_;
        PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv_;
        PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s_;
        PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv_;
        PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f_;
        PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv_;
        PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s_;
        PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv_;
        PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f_;
        PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv_;
        PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s_;
        PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv_;
        PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv_;
        PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv_;
        PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv_;
        PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv_;
        PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv_;
        PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv_;
        PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv_;
        PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub_;
        PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv_;
        PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv_;
        PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv_;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_;
        PFNGLDRAWBUFFERSPROC glDrawBuffers_;
#endif
        PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation_;
        PFNGLBINDBUFFERBASEPROC       glBindBufferBase_;
        PFNGLBINDBUFFERRANGEPROC      glBindBufferRange_;

        // GL_EXT_framebuffer_object
        PFNGLBINDRENDERBUFFERPROC        glBindRenderbuffer_;
        PFNGLDELETERENDERBUFFERSPROC     glDeleteRenderbuffers_;
        PFNGLGENFRAMEBUFFERSPROC         glGenRenderbuffers_;
        PFNGLRENDERBUFFERSTORAGEPROC     glRenderbufferStorage_;
        PFNGLCHECKFRAMEBUFFERSTATUSPROC  glCheckFramebufferStatus_;
        PFNGLBINDFRAMEBUFFERPROC         glBindFramebuffer_;
        PFNGLDELETEFRAMEBUFFERSPROC      glDeleteFramebuffers_;
        PFNGLGENFRAMEBUFFERSPROC         glGenFramebuffers_;
        PFNGLFRAMEBUFFERTEXTURE2DPROC    glFramebufferTexture2D_;
        PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer_;
        PFNGLGENERATEMIPMAPPROC          glGenerateMipmap_;

        // GL_EXT_framebuffer_blit
        PFNGLBLITFRAMEBUFFERPROC         glBlitFramebuffer_;

        PFNGLMAPBUFFERRANGEPROC         glMapBufferRange_;
        PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange_;

        PFNGLGETUNIFORMINDICESPROC       glGetUniformIndices_;
        PFNGLGETACTIVEUNIFORMSIVPROC     glGetActiveUniformsiv_;
        PFNGLGETUNIFORMBLOCKINDEXPROC    glGetUniformBlockIndex_;
        PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv_;
        PFNGLUNIFORMBLOCKBINDINGPROC     glUniformBlockBinding_;

        PFNGLBINDVERTEXARRAYPROC    glBindVertexArray_;
        PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_;
        PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays_;
        PFNGLISVERTEXARRAYPROC      glIsVertexArray_;

        bool gl_init();

        /* glemu */
        const char * const glemu_attribnames[GLEMU_MAXATTRIBS] = { "vvertex", "vcolor", "vtexcoord0", "vtexcoord1", "vnormal", "vtangent", "vboneweight", "vboneindex" };
        //ucharbuf glemu_attribbuf;

        unsigned char *glemu_attribdata;

        glemu_attribinfo glemu_attribdefs[GLEMU_MAXATTRIBS];
        glemu_attribinfo glemu_lastattribs[GLEMU_MAXATTRIBS];
        int glemu_enabled = 0;
        int glemu_numattribs = 0;
        int glemu_attribmask = 0;
        int glemu_numlastattribs = 0;
        int glemu_lastattribmask = 0;
        int glemu_vertexsize = 0;
        int glemu_lastvertexsize = 0;

        // Specifies what kind of primitives to render
        GLenum glemu_primtype = GL_TRIANGLES;

        unsigned char *glemu_lastbuf = nullptr;

        bool glemu_changedattribs = false;
        std::vector<GLint> glemu_multidrawstart;
        std::vector<GLsizei> glemu_multidrawcount;
        short glemu_maxquads = 0x10000/4;
        GLuint glemu_quadindexes = 0;
        bool glemu_quadsenabled = false;

        // pointer to buffer object holding name(s) generated by glGenBuffers
        GLuint glemu_vbo = 0;

        /*
         * You can use whatever size you like when allocating storage for buffer objects. However, there are some rules to bear in mind.
         * Making lots of tiny buffers (with sizes on the order of Kilobytes) can cause the driver problems. Some drivers can only make
         * so many allocations from graphics memory, regardless of what size those allocations are. Note that "lots of" could mean thousands.
         * So putting smaller objects in one large buffer is a good idea. There are two competing issues with buffer sizes.
         * Larger buffers means putting multiple objects in one buffer. This allows you to render more objects without having to change buffer object state. Thus improving performance.
         * Larger buffers means putting multiple objects in one buffer. However, mapping a buffer means that the entire buffer cannot be used
         * (unless you map it persistently). So if you have many objects in one, and you need to map the data for one object, then the others will not be usable while you are modifying that one object.
         */
        int glemu_maxvboxsize = 500000;

        //  Specifies the starting offset within the buffer of the range to be mapped.
        int glemu_vbooffset = 4*1024*1024;
        GLuint glemu_defaultvao = 0;


        void Glemu_begin(GLenum mode);
        void Glemu_begin(GLenum mode, int numverts);


        void Glemu_cleanup();
        void Glemu_disable();
        void Glemu_enablequads();
        void Glemu_disablequads();
        void Glemu_drawquads(int offset, int count);
        void Glemu_defattrib(int type, int size, int format);
        void Glemu_defattribs(const char *fmt);
        inline void Glemu_setattrib(const glemu_attribinfo &a, unsigned char *buf);
        inline void Glemu_unsetattrib(const glemu_attribinfo &a);
        inline void Glemu_setattribs(unsigned char *buf);
        void Glemu_multidraw();
        void Glemu_setup();
        void Glemu_forcedisable();

        int Glemu_end();

        void defvertex(int size = 3, int format = GL_FLOAT);
        void defcolor(int size = 3, int format = GL_FLOAT);
        void deftexcoord0(int size =2, int format = GL_FLOAT);
        void deftexcoord1(int size = 2, int format = GL_FLOAT);
        void defnormal(int size =3, int format = GL_FLOAT);
        void deftangent(int size = 4, int format = GL_FLOAT);
        void defboneweight(int size = 4, int format = GL_UNSIGNED_BYTE);
        void defboneindex(int size = 4, int format = GL_UNSIGNED_BYTE);
    };

}
#endif //SAUERKRAUT_OPENGL_H
