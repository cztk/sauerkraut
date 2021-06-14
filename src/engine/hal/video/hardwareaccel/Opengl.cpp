//
// Created by ztk on 2021-06-14.
//

#include "Opengl.h"

namespace kraut::engine::hal::video::sdl::hardwareaccel {


    Opengl::Opengl(engine::Engine *pEngine, config::Config *pConfig, log::LogHandler *pLoghandler) :
    _engine(pEngine), _config(pConfig), _logHandler(pLoghandler) {

    }

    void Opengl::parseglexts()
    {
        if(glversion >= 300)
        {
            GLint numexts = 0;
            glGetIntegerv(GL_NUM_EXTENSIONS, &numexts);

            for(int i=0;i<numexts;i++) {
                std::string ext = ((const char *)glGetStringi_(GL_EXTENSIONS, i));
                glexts.insert(std::move(ext));
            }
        }
        else
        {
            std::string exts = (const char *)glGetString(GL_EXTENSIONS);
            glexts = utils::StringHelper::string_split_toUset(exts);
        }
    }

    bool Opengl::hasext(const char *ext)
    {
        return glexts.contains(std::string(ext));
    }

    //TODO code so ugly
    bool Opengl::checkextensions() {

        const char *vendor = (const char *)glGetString(GL_VENDOR);
        const char *renderer = (const char *)glGetString(GL_RENDERER);
        const char *version = (const char *)glGetString(GL_VERSION);
        //TODO console
//        conoutf(CON_INIT, "Renderer: %s (%s)", renderer, vendor);
//        conoutf(CON_INIT, "Driver: %s", version);

        bool mesa = false, intel = false, ati = false, nvidia = false;
        if(strstr(renderer, "Mesa") || strstr(version, "Mesa"))
        {
            mesa = true;
            if(strstr(renderer, "Intel")) intel = true;
        }
        else if(strstr(vendor, "NVIDIA"))
            nvidia = true;
        else if(strstr(vendor, "ATI") || strstr(vendor, "Advanced Micro Devices"))
            ati = true;
        else if(strstr(vendor, "Intel"))
            intel = true;

        uint glmajorversion, glminorversion;
        if(sscanf(version, " %u.%u", &glmajorversion, &glminorversion) != 2) glversion = 100;
        else glversion = glmajorversion*100 + glminorversion*10;

        if(glversion < 200) {
            return false;
            //TODO log message
//            fatal("OpenGL 2.0 or greater is required!");
        }

#ifdef WIN32
        glActiveTexture_ =            (PFNGLACTIVETEXTUREPROC)            getprocaddress("glActiveTexture");

    glBlendEquation_ =            (PFNGLBLENDEQUATIONPROC)            getprocaddress("glBlendEquation");
    glBlendColor_ =               (PFNGLBLENDCOLORPROC)               getprocaddress("glBlendColor");

    glTexImage3D_ =               (PFNGLTEXIMAGE3DPROC)               getprocaddress("glTexImage3D");
    glTexSubImage3D_ =            (PFNGLTEXSUBIMAGE3DPROC)            getprocaddress("glTexSubImage3D");
    glCopyTexSubImage3D_ =        (PFNGLCOPYTEXSUBIMAGE3DPROC)        getprocaddress("glCopyTexSubImage3D");

    glCompressedTexImage3D_ =     (PFNGLCOMPRESSEDTEXIMAGE3DPROC)     getprocaddress("glCompressedTexImage3D");
    glCompressedTexImage2D_ =     (PFNGLCOMPRESSEDTEXIMAGE2DPROC)     getprocaddress("glCompressedTexImage2D");
    glCompressedTexSubImage3D_ =  (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)  getprocaddress("glCompressedTexSubImage3D");
    glCompressedTexSubImage2D_ =  (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)  getprocaddress("glCompressedTexSubImage2D");
    glGetCompressedTexImage_ =    (PFNGLGETCOMPRESSEDTEXIMAGEPROC)    getprocaddress("glGetCompressedTexImage");

    glDrawRangeElements_ =        (PFNGLDRAWRANGEELEMENTSPROC)        getprocaddress("glDrawRangeElements");
#endif

#ifndef __APPLE__
        glMultiDrawArrays_ =          (PFNGLMULTIDRAWARRAYSPROC)          getprocaddress("glMultiDrawArrays");
        glMultiDrawElements_ =        (PFNGLMULTIDRAWELEMENTSPROC)        getprocaddress("glMultiDrawElements");

        glBlendFuncSeparate_ =        (PFNGLBLENDFUNCSEPARATEPROC)        getprocaddress("glBlendFuncSeparate");
        glBlendEquationSeparate_ =    (PFNGLBLENDEQUATIONSEPARATEPROC)    getprocaddress("glBlendEquationSeparate");
        glStencilOpSeparate_ =        (PFNGLSTENCILOPSEPARATEPROC)        getprocaddress("glStencilOpSeparate");
        glStencilFuncSeparate_ =      (PFNGLSTENCILFUNCSEPARATEPROC)      getprocaddress("glStencilFuncSeparate");
        glStencilMaskSeparate_ =      (PFNGLSTENCILMASKSEPARATEPROC)      getprocaddress("glStencilMaskSeparate");

        glGenBuffers_ =               (PFNGLGENBUFFERSPROC)               getprocaddress("glGenBuffers");
        glBindBuffer_ =               (PFNGLBINDBUFFERPROC)               getprocaddress("glBindBuffer");
        glMapBuffer_ =                (PFNGLMAPBUFFERPROC)                getprocaddress("glMapBuffer");
        glUnmapBuffer_ =              (PFNGLUNMAPBUFFERPROC)              getprocaddress("glUnmapBuffer");
        glBufferData_ =               (PFNGLBUFFERDATAPROC)               getprocaddress("glBufferData");
        glBufferSubData_ =            (PFNGLBUFFERSUBDATAPROC)            getprocaddress("glBufferSubData");
        glDeleteBuffers_ =            (PFNGLDELETEBUFFERSPROC)            getprocaddress("glDeleteBuffers");
        glGetBufferSubData_ =         (PFNGLGETBUFFERSUBDATAPROC)         getprocaddress("glGetBufferSubData");

        glGetQueryiv_ =               (PFNGLGETQUERYIVPROC)               getprocaddress("glGetQueryiv");
        glGenQueries_ =               (PFNGLGENQUERIESPROC)               getprocaddress("glGenQueries");
        glDeleteQueries_ =            (PFNGLDELETEQUERIESPROC)            getprocaddress("glDeleteQueries");
        glBeginQuery_ =               (PFNGLBEGINQUERYPROC)               getprocaddress("glBeginQuery");
        glEndQuery_ =                 (PFNGLENDQUERYPROC)                 getprocaddress("glEndQuery");
        glGetQueryObjectiv_ =         (PFNGLGETQUERYOBJECTIVPROC)         getprocaddress("glGetQueryObjectiv");
        glGetQueryObjectuiv_ =        (PFNGLGETQUERYOBJECTUIVPROC)        getprocaddress("glGetQueryObjectuiv");

        glCreateProgram_ =            (PFNGLCREATEPROGRAMPROC)            getprocaddress("glCreateProgram");
        glDeleteProgram_ =            (PFNGLDELETEPROGRAMPROC)            getprocaddress("glDeleteProgram");
        glUseProgram_ =               (PFNGLUSEPROGRAMPROC)               getprocaddress("glUseProgram");
        glCreateShader_ =             (PFNGLCREATESHADERPROC)             getprocaddress("glCreateShader");
        glDeleteShader_ =             (PFNGLDELETESHADERPROC)             getprocaddress("glDeleteShader");
        glShaderSource_ =             (PFNGLSHADERSOURCEPROC)             getprocaddress("glShaderSource");
        glCompileShader_ =            (PFNGLCOMPILESHADERPROC)            getprocaddress("glCompileShader");
        glGetShaderiv_ =              (PFNGLGETSHADERIVPROC)              getprocaddress("glGetShaderiv");
        glGetProgramiv_ =             (PFNGLGETPROGRAMIVPROC)             getprocaddress("glGetProgramiv");
        glAttachShader_ =             (PFNGLATTACHSHADERPROC)             getprocaddress("glAttachShader");
        glGetProgramInfoLog_ =        (PFNGLGETPROGRAMINFOLOGPROC)        getprocaddress("glGetProgramInfoLog");
        glGetShaderInfoLog_ =         (PFNGLGETSHADERINFOLOGPROC)         getprocaddress("glGetShaderInfoLog");
        glLinkProgram_ =              (PFNGLLINKPROGRAMPROC)              getprocaddress("glLinkProgram");
        glGetUniformLocation_ =       (PFNGLGETUNIFORMLOCATIONPROC)       getprocaddress("glGetUniformLocation");
        glUniform1f_ =                (PFNGLUNIFORM1FPROC)                getprocaddress("glUniform1f");
        glUniform2f_ =                (PFNGLUNIFORM2FPROC)                getprocaddress("glUniform2f");
        glUniform3f_ =                (PFNGLUNIFORM3FPROC)                getprocaddress("glUniform3f");
        glUniform4f_ =                (PFNGLUNIFORM4FPROC)                getprocaddress("glUniform4f");
        glUniform1fv_ =               (PFNGLUNIFORM1FVPROC)               getprocaddress("glUniform1fv");
        glUniform2fv_ =               (PFNGLUNIFORM2FVPROC)               getprocaddress("glUniform2fv");
        glUniform3fv_ =               (PFNGLUNIFORM3FVPROC)               getprocaddress("glUniform3fv");
        glUniform4fv_ =               (PFNGLUNIFORM4FVPROC)               getprocaddress("glUniform4fv");
        glUniform1i_ =                (PFNGLUNIFORM1IPROC)                getprocaddress("glUniform1i");
        glUniform2i_ =                (PFNGLUNIFORM2IPROC)                getprocaddress("glUniform2i");
        glUniform3i_ =                (PFNGLUNIFORM3IPROC)                getprocaddress("glUniform3i");
        glUniform4i_ =                (PFNGLUNIFORM4IPROC)                getprocaddress("glUniform4i");
        glUniform1iv_ =               (PFNGLUNIFORM1IVPROC)               getprocaddress("glUniform1iv");
        glUniform2iv_ =               (PFNGLUNIFORM2IVPROC)               getprocaddress("glUniform2iv");
        glUniform3iv_ =               (PFNGLUNIFORM3IVPROC)               getprocaddress("glUniform3iv");
        glUniform4iv_ =               (PFNGLUNIFORM4IVPROC)               getprocaddress("glUniform4iv");
        glUniformMatrix2fv_ =         (PFNGLUNIFORMMATRIX2FVPROC)         getprocaddress("glUniformMatrix2fv");
        glUniformMatrix3fv_ =         (PFNGLUNIFORMMATRIX3FVPROC)         getprocaddress("glUniformMatrix3fv");
        glUniformMatrix4fv_ =         (PFNGLUNIFORMMATRIX4FVPROC)         getprocaddress("glUniformMatrix4fv");
        glBindAttribLocation_ =       (PFNGLBINDATTRIBLOCATIONPROC)       getprocaddress("glBindAttribLocation");
        glGetActiveUniform_ =         (PFNGLGETACTIVEUNIFORMPROC)         getprocaddress("glGetActiveUniform");
        glEnableVertexAttribArray_ =  (PFNGLENABLEVERTEXATTRIBARRAYPROC)  getprocaddress("glEnableVertexAttribArray");
        glDisableVertexAttribArray_ = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) getprocaddress("glDisableVertexAttribArray");

        glVertexAttrib1f_ =           (PFNGLVERTEXATTRIB1FPROC)           getprocaddress("glVertexAttrib1f");
        glVertexAttrib1fv_ =          (PFNGLVERTEXATTRIB1FVPROC)          getprocaddress("glVertexAttrib1fv");
        glVertexAttrib1s_ =           (PFNGLVERTEXATTRIB1SPROC)           getprocaddress("glVertexAttrib1s");
        glVertexAttrib1sv_ =          (PFNGLVERTEXATTRIB1SVPROC)          getprocaddress("glVertexAttrib1sv");
        glVertexAttrib2f_ =           (PFNGLVERTEXATTRIB2FPROC)           getprocaddress("glVertexAttrib2f");
        glVertexAttrib2fv_ =          (PFNGLVERTEXATTRIB2FVPROC)          getprocaddress("glVertexAttrib2fv");
        glVertexAttrib2s_ =           (PFNGLVERTEXATTRIB2SPROC)           getprocaddress("glVertexAttrib2s");
        glVertexAttrib2sv_ =          (PFNGLVERTEXATTRIB2SVPROC)          getprocaddress("glVertexAttrib2sv");
        glVertexAttrib3f_ =           (PFNGLVERTEXATTRIB3FPROC)           getprocaddress("glVertexAttrib3f");
        glVertexAttrib3fv_ =          (PFNGLVERTEXATTRIB3FVPROC)          getprocaddress("glVertexAttrib3fv");
        glVertexAttrib3s_ =           (PFNGLVERTEXATTRIB3SPROC)           getprocaddress("glVertexAttrib3s");
        glVertexAttrib3sv_ =          (PFNGLVERTEXATTRIB3SVPROC)          getprocaddress("glVertexAttrib3sv");
        glVertexAttrib4f_ =           (PFNGLVERTEXATTRIB4FPROC)           getprocaddress("glVertexAttrib4f");
        glVertexAttrib4fv_ =          (PFNGLVERTEXATTRIB4FVPROC)          getprocaddress("glVertexAttrib4fv");
        glVertexAttrib4s_ =           (PFNGLVERTEXATTRIB4SPROC)           getprocaddress("glVertexAttrib4s");
        glVertexAttrib4sv_ =          (PFNGLVERTEXATTRIB4SVPROC)          getprocaddress("glVertexAttrib4sv");
        glVertexAttrib4bv_ =          (PFNGLVERTEXATTRIB4BVPROC)          getprocaddress("glVertexAttrib4bv");
        glVertexAttrib4iv_ =          (PFNGLVERTEXATTRIB4IVPROC)          getprocaddress("glVertexAttrib4iv");
        glVertexAttrib4ubv_ =         (PFNGLVERTEXATTRIB4UBVPROC)         getprocaddress("glVertexAttrib4ubv");
        glVertexAttrib4uiv_ =         (PFNGLVERTEXATTRIB4UIVPROC)         getprocaddress("glVertexAttrib4uiv");
        glVertexAttrib4usv_ =         (PFNGLVERTEXATTRIB4USVPROC)         getprocaddress("glVertexAttrib4usv");
        glVertexAttrib4Nbv_ =         (PFNGLVERTEXATTRIB4NBVPROC)         getprocaddress("glVertexAttrib4Nbv");
        glVertexAttrib4Niv_ =         (PFNGLVERTEXATTRIB4NIVPROC)         getprocaddress("glVertexAttrib4Niv");
        glVertexAttrib4Nub_ =         (PFNGLVERTEXATTRIB4NUBPROC)         getprocaddress("glVertexAttrib4Nub");
        glVertexAttrib4Nubv_ =        (PFNGLVERTEXATTRIB4NUBVPROC)        getprocaddress("glVertexAttrib4Nubv");
        glVertexAttrib4Nuiv_ =        (PFNGLVERTEXATTRIB4NUIVPROC)        getprocaddress("glVertexAttrib4Nuiv");
        glVertexAttrib4Nusv_ =        (PFNGLVERTEXATTRIB4NUSVPROC)        getprocaddress("glVertexAttrib4Nusv");
        glVertexAttribPointer_ =      (PFNGLVERTEXATTRIBPOINTERPROC)      getprocaddress("glVertexAttribPointer");

        glDrawBuffers_ =              (PFNGLDRAWBUFFERSPROC)              getprocaddress("glDrawBuffers");
#endif

        if(glversion >= 300)
        {
            glGetStringi_ =            (PFNGLGETSTRINGIPROC)          getprocaddress("glGetStringi");
            glBindFragDataLocation_ =  (PFNGLBINDFRAGDATALOCATIONPROC)getprocaddress("glBindFragDataLocation");
        }

        const char *glslstr = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
        uint glslmajorversion, glslminorversion;
        if(glslstr && sscanf(glslstr, " %u.%u", &glslmajorversion, &glslminorversion) == 2) glslversion = glslmajorversion*100 + glslminorversion;

        if(glslversion < 120){
          //TODO log
          //fatal("GLSL 1.20 or greater is required!");
          return false;
        }

        parseglexts();

        GLint val;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
        hwtexsize = val;
        glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &val);
        hwcubetexsize = val;

        if(glversion >= 300 || hasext("GL_ARB_texture_float") || hasext("GL_ATI_texture_float"))
        {
            hasTF = true;
            if(glversion < 300 && dbgexts){
              //TODO console
              // conoutf(CON_INIT, "Using GL_ARB_texture_float extension.");
            }
            shadowmap = 1;
            smoothshadowmappeel = 1;
        }

        if(glversion >= 300 || hasext("GL_ARB_texture_rg"))
        {
            hasTRG = true;
            if(glversion < 300 && dbgexts) {
                //TODO console
                //conoutf(CON_INIT, "Using GL_ARB_texture_rg extension.");
            }
        }

        if(glversion >= 300 || hasext("GL_ARB_framebuffer_object"))
        {
            glBindRenderbuffer_        = (PFNGLBINDRENDERBUFFERPROC)       getprocaddress("glBindRenderbuffer");
            glDeleteRenderbuffers_     = (PFNGLDELETERENDERBUFFERSPROC)    getprocaddress("glDeleteRenderbuffers");
            glGenRenderbuffers_        = (PFNGLGENFRAMEBUFFERSPROC)        getprocaddress("glGenRenderbuffers");
            glRenderbufferStorage_     = (PFNGLRENDERBUFFERSTORAGEPROC)    getprocaddress("glRenderbufferStorage");
            glCheckFramebufferStatus_  = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) getprocaddress("glCheckFramebufferStatus");
            glBindFramebuffer_         = (PFNGLBINDFRAMEBUFFERPROC)        getprocaddress("glBindFramebuffer");
            glDeleteFramebuffers_      = (PFNGLDELETEFRAMEBUFFERSPROC)     getprocaddress("glDeleteFramebuffers");
            glGenFramebuffers_         = (PFNGLGENFRAMEBUFFERSPROC)        getprocaddress("glGenFramebuffers");
            glFramebufferTexture2D_    = (PFNGLFRAMEBUFFERTEXTURE2DPROC)   getprocaddress("glFramebufferTexture2D");
            glFramebufferRenderbuffer_ = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)getprocaddress("glFramebufferRenderbuffer");
            glGenerateMipmap_          = (PFNGLGENERATEMIPMAPPROC)         getprocaddress("glGenerateMipmap");
            glBlitFramebuffer_         = (PFNGLBLITFRAMEBUFFERPROC)        getprocaddress("glBlitFramebuffer");
            hasAFBO = hasFBO = hasFBB = hasDS = true;
            if(glversion < 300 && dbgexts){
                //TODO console
                //conoutf(CON_INIT, "Using GL_ARB_framebuffer_object extension.");
            }
        }
        else if(hasext("GL_EXT_framebuffer_object"))
        {
            glBindRenderbuffer_        = (PFNGLBINDRENDERBUFFERPROC)       getprocaddress("glBindRenderbufferEXT");
            glDeleteRenderbuffers_     = (PFNGLDELETERENDERBUFFERSPROC)    getprocaddress("glDeleteRenderbuffersEXT");
            glGenRenderbuffers_        = (PFNGLGENFRAMEBUFFERSPROC)        getprocaddress("glGenRenderbuffersEXT");
            glRenderbufferStorage_     = (PFNGLRENDERBUFFERSTORAGEPROC)    getprocaddress("glRenderbufferStorageEXT");
            glCheckFramebufferStatus_  = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) getprocaddress("glCheckFramebufferStatusEXT");
            glBindFramebuffer_         = (PFNGLBINDFRAMEBUFFERPROC)        getprocaddress("glBindFramebufferEXT");
            glDeleteFramebuffers_      = (PFNGLDELETEFRAMEBUFFERSPROC)     getprocaddress("glDeleteFramebuffersEXT");
            glGenFramebuffers_         = (PFNGLGENFRAMEBUFFERSPROC)        getprocaddress("glGenFramebuffersEXT");
            glFramebufferTexture2D_    = (PFNGLFRAMEBUFFERTEXTURE2DPROC)   getprocaddress("glFramebufferTexture2DEXT");
            glFramebufferRenderbuffer_ = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)getprocaddress("glFramebufferRenderbufferEXT");
            glGenerateMipmap_          = (PFNGLGENERATEMIPMAPPROC)         getprocaddress("glGenerateMipmapEXT");
            hasFBO = true;
            if(dbgexts) {
                //TODO console
                //conoutf(CON_INIT, "Using GL_EXT_framebuffer_object extension.");
            }

            if(hasext("GL_EXT_framebuffer_blit"))
            {
                glBlitFramebuffer_     = (PFNGLBLITFRAMEBUFFERPROC)        getprocaddress("glBlitFramebufferEXT");
                hasFBB = true;
                //TODO
                //if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_framebuffer_blit extension.");
            }

            if(hasext("GL_EXT_packed_depth_stencil") || hasext("GL_NV_packed_depth_stencil"))
            {
                hasDS = true;
                //TODO
                //if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_packed_depth_stencil extension.");
            }
        }
        else{
            return false;
            //TODO
            //fatal("Framebuffer object support is required!");
        }

        //TODO set fpdepthfx
        //extern int fpdepthfx;
        if(ati)
        {
            //conoutf(CON_WARN, "WARNING: ATI cards may show garbage in skybox. (use \"/ati_skybox_bug 1\" to fix)");

            minimizetcusage = 1;
            if(hasTF && hasTRG) fpdepthfx = 1;
            // On Catalyst 10.2, issuing an occlusion query on the first draw using a given cubemap texture causes a nasty crash
            ati_cubemap_bug = 1;
        }
        else if(nvidia)
        {
            reservevpparams = 10;
            rtsharefb = 0; // work-around for strange driver stalls involving when using many FBOs

            if(glversion < 300 && !hasext("GL_EXT_gpu_shader4")) filltjoints = 0; // DX9 or less NV cards seem to not cause many sparklies

            if(hasTF && hasTRG) fpdepthfx = 1;
        }
        else
        {
            if(intel)
            {
#ifdef WIN32
                intel_vertexarray_bug = 1;
            // MapBufferRange is buggy on older Intel drivers on Windows
            if(glversion <= 310) intel_mapbufferrange_bug = 1;
#endif
            }

            reservevpparams = 20;

            if(mesa) mesa_swap_bug = 1;
        }

        if(glversion >= 300 || hasext("GL_ARB_map_buffer_range"))
        {
            glMapBufferRange_         = (PFNGLMAPBUFFERRANGEPROC)        getprocaddress("glMapBufferRange");
            glFlushMappedBufferRange_ = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)getprocaddress("glFlushMappedBufferRange");
            hasMBR = true;
            //TODO
            //if(glversion < 300 && dbgexts) conoutf(CON_INIT, "Using GL_ARB_map_buffer_range.");
        }

        if(glversion >= 310 || hasext("GL_ARB_uniform_buffer_object"))
        {
            glGetUniformIndices_       = (PFNGLGETUNIFORMINDICESPROC)      getprocaddress("glGetUniformIndices");
            glGetActiveUniformsiv_     = (PFNGLGETACTIVEUNIFORMSIVPROC)    getprocaddress("glGetActiveUniformsiv");
            glGetUniformBlockIndex_    = (PFNGLGETUNIFORMBLOCKINDEXPROC)   getprocaddress("glGetUniformBlockIndex");
            glGetActiveUniformBlockiv_ = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)getprocaddress("glGetActiveUniformBlockiv");
            glUniformBlockBinding_     = (PFNGLUNIFORMBLOCKBINDINGPROC)    getprocaddress("glUniformBlockBinding");
            glBindBufferBase_          = (PFNGLBINDBUFFERBASEPROC)         getprocaddress("glBindBufferBase");
            glBindBufferRange_         = (PFNGLBINDBUFFERRANGEPROC)        getprocaddress("glBindBufferRange");

            useubo = 1;
            hasUBO = true;
            //TODO
            //if(glversion < 310 && dbgexts) conoutf(CON_INIT, "Using GL_ARB_uniform_buffer_object extension.");
        }

        if(glversion >= 300 || hasext("GL_ARB_vertex_array_object"))
        {
            glBindVertexArray_ =    (PFNGLBINDVERTEXARRAYPROC)   getprocaddress("glBindVertexArray");
            glDeleteVertexArrays_ = (PFNGLDELETEVERTEXARRAYSPROC)getprocaddress("glDeleteVertexArrays");
            glGenVertexArrays_ =    (PFNGLGENVERTEXARRAYSPROC)   getprocaddress("glGenVertexArrays");
            glIsVertexArray_ =      (PFNGLISVERTEXARRAYPROC)     getprocaddress("glIsVertexArray");
            hasVAO = true;
            //TODO
            //if(glversion < 300 && dbgexts) conoutf(CON_INIT, "Using GL_ARB_vertex_array_object extension.");
        }
        else if(hasext("GL_APPLE_vertex_array_object"))
        {
            glBindVertexArray_ =    (PFNGLBINDVERTEXARRAYPROC)   getprocaddress("glBindVertexArrayAPPLE");
            glDeleteVertexArrays_ = (PFNGLDELETEVERTEXARRAYSPROC)getprocaddress("glDeleteVertexArraysAPPLE");
            glGenVertexArrays_ =    (PFNGLGENVERTEXARRAYSPROC)   getprocaddress("glGenVertexArraysAPPLE");
            glIsVertexArray_ =      (PFNGLISVERTEXARRAYPROC)     getprocaddress("glIsVertexArrayAPPLE");
            hasVAO = true;
            //TODO
            //if(dbgexts) conoutf(CON_INIT, "Using GL_APPLE_vertex_array_object extension.");
        }

        if(glversion >= 330 || hasext("GL_ARB_texture_swizzle") || hasext("GL_EXT_texture_swizzle"))
        {
            hasTSW = true;
            //TODO
//            if(glversion < 330 && dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_swizzle extension.");
        }

        if(hasext("GL_EXT_texture_compression_s3tc"))
        {
            hasS3TC = true;
#ifdef __APPLE__
            usetexcompress = 1;
#else
            if(!mesa) usetexcompress = 2;
#endif
            //TODO
//            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_s3tc extension.");
        }
        else if(hasext("GL_EXT_texture_compression_dxt1") && hasext("GL_ANGLE_texture_compression_dxt3") && hasext("GL_ANGLE_texture_compression_dxt5"))
        {
            hasS3TC = true;
            //TODO
//            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_dxt1 extension.");
        }
        if(hasext("GL_3DFX_texture_compression_FXT1"))
        {
            hasFXT1 = true;
            if(mesa) usetexcompress = std::max(usetexcompress, 1);
            //TODO
//            if(dbgexts) conoutf(CON_INIT, "Using GL_3DFX_texture_compression_FXT1.");
        }
        if(hasext("GL_EXT_texture_compression_latc"))
        {
            hasLATC = true;
            //TODO
//            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_latc extension.");
        }
        if(glversion >= 300 || hasext("GL_ARB_texture_compression_rgtc") || hasext("GL_EXT_texture_compression_rgtc"))
        {
            hasRGTC = true;
            //TODO
//            if(glversion < 300 && dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_compression_rgtc extension.");
        }

        if(hasext("GL_EXT_texture_filter_anisotropic"))
        {
            GLint val;
            glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &val);
            hwmaxaniso = val;
            hasAF = true;
            //TODO
//            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_filter_anisotropic extension.");
        }

        if(glversion >= 300 || hasext("GL_EXT_gpu_shader4"))
        {
            // on DX10 or above class cards (i.e. GF8 or RadeonHD) enable expensive features
            grass = 1;
            waterfallrefract = 1;
            glare = 1;
            maxdynlights = 5;
            depthfxsize = 10;
            blurdepthfx = 0;
            texcompress = std::max(texcompress, 1024 + 1);
        }
        return true;
    }

    bool Opengl::init() {
        if(checkextensions()) {
            gl_init();
            return true;
        }
        return false;
    }

    void *Opengl::getprocaddress(const char *name) {
        return SDL_GL_GetProcAddress(name);
    }

    void Opengl::gl_setuptexcompress()
    {
        if(!usetexcompress) return;

        GLenum hint = GL_DONT_CARE;
        switch(texcompressquality)
        {
            case 1: hint = GL_NICEST; break;
            case 0: hint = GL_FASTEST; break;
        }
        glHint(GL_TEXTURE_COMPRESSION_HINT, hint);
    }

    void Opengl::resizeViewport(int width, int height, int x, int y)
    {
        glViewport(x, y, width, height);
    }

    bool Opengl::gl_init() {
        glClearColor(0, 0, 0, 0);
        glClearDepth(1);
        glDepthFunc(GL_LESS);
        glDisable(GL_DEPTH_TEST);

        glEnable(GL_LINE_SMOOTH);
        //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);

        gle::setup();

        setupshaders();

        gl_setuptexcompress();

        resizeViewport(_config->engine.screen_w, _config->engine.screen_h, 0, 0);
        return true;
    }
}