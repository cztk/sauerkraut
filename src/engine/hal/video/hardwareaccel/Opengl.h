//
// Created by ztk on 2021-06-14.
//

#ifndef SAUERKRAUT_OPENGL_H
#define SAUERKRAUT_OPENGL_H

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <string>
#include "../../../../utils/stringhelper.h"
#include "../iHardwareAccel.h"
#include "../../../../log/LogHandler.h"

namespace kraut::engine::hal::video::sdl::hardwareaccel {
    class Opengl final : public iHardwareAccel {
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




    };

}
#endif //SAUERKRAUT_OPENGL_H
