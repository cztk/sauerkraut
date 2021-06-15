//
// Created by ztk on 2021-06-14.
//

#include "Opengl.h"

namespace kraut::engine::hal::video::sdl::renderer::opengl {


    Opengl::Opengl(log::LogHandler *pLoghandler) : _logHandler(pLoghandler) {

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

    void Opengl::setuptexcompress(int texcompressslevel)
    {
        usetexcompress = 1;

        GLenum hint = GL_DONT_CARE;
        switch(texcompressslevel)
        {
            case 1:
                texcompress = 1;
                hint = GL_NICEST;
                break;
            case 0:
                texcompress = 0;
                hint = GL_FASTEST;
                break;
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

        Glemu_setup();

        setupshaders();

        return true;
    }


    void Opengl::Glemu_begin(GLenum mode)
    {
        glemu_primtype = mode;
    }

    void Opengl::Glemu_begin(GLenum mode, int numverts)
    {

        glemu_primtype = mode;
        if(glversion >= 300 && !intel_mapbufferrange_bug)
        {
            // we set the glemu_vertexsize to our needed data size before (def...) takes GL_FLOAT amount of space e.g.
            // multiplied with our number of vertexes we get the len of our total data
            int len = numverts * glemu_vertexsize;

            // if we have data in our buffer already, we need to check if our new data can fit or if
            // we need a new buffer.
            //TODO what happens with the previously reserved?
            if(glemu_vbooffset + len >= glemu_maxvboxsize)
            {
                len = std::min(len, glemu_maxvboxsize);

                // get 1 buffer object name ref to glemu_vbo
                if(!glemu_vbo){
                    glGenBuffers_(1, &glemu_vbo);
                }

                // bind qlemu_vbo as Vertex attributes target
                glBindBuffer_(GL_ARRAY_BUFFER, glemu_vbo);

                // create and initialize buffer object's data store
                // void glBufferData( 	GLenum target, GLsizeiptr size, onst void * data, GLenum usage);
                glBufferData_(GL_ARRAY_BUFFER, glemu_maxvboxsize, nullptr, GL_STREAM_DRAW);

                glemu_vbooffset = 0;
            }
            else if(!glemu_lastvertexsize){
                glBindBuffer_(GL_ARRAY_BUFFER, glemu_vbo);
            }
            void *buf = glMapBufferRange_(GL_ARRAY_BUFFER, glemu_vbooffset, len, GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT|GL_MAP_UNSYNCHRONIZED_BIT);
            if(buf) {
                glemu_attribbuf.reset((unsigned char *) buf, len);
            }
        }
    }



    void Opengl::Glemu_enablequads()
    {
        glemu_quadsenabled = true;

        if(glversion < 300) return;

        if(glemu_quadindexes)
        {
            glBindBuffer_(GL_ELEMENT_ARRAY_BUFFER, glemu_quadindexes);
            return;
        }

        glGenBuffers_(1, &glemu_quadindexes);
        unsigned short *data = new unsigned short[glemu_maxquads*6], *dst = data;
        for(int idx = 0; idx < glemu_maxquads*4; idx += 4, dst += 6)
        {
            dst[0] = idx;
            dst[1] = idx + 1;
            dst[2] = idx + 2;
            dst[3] = idx + 0;
            dst[4] = idx + 2;
            dst[5] = idx + 3;
        }
        glBindBuffer_(GL_ELEMENT_ARRAY_BUFFER, glemu_quadindexes);
        glBufferData_(GL_ELEMENT_ARRAY_BUFFER, glemu_maxquads*6*sizeof(unsigned short), data, GL_STATIC_DRAW);
        delete[] data;
    }

    void Opengl::Glemu_disablequads()
    {
        glemu_quadsenabled = false;

        if(glversion < 300) return;

        glBindBuffer_(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Opengl::Glemu_drawquads(int offset, int count)
    {
        if(count <= 0) return;
        if(glversion < 300)
        {
            glDrawArrays(GL_QUADS, offset*4, count*4);
            return;
        }
        if(offset + count > glemu_maxquads)
        {
            if(offset >= glemu_maxquads) return;
            count = glemu_maxquads - offset;
        }
        glDrawRangeElements_(GL_TRIANGLES, offset*4, (offset + count)*4-1, count*6, GL_UNSIGNED_SHORT, (ushort *)0 + offset*6);
    }

    void Opengl::Glemu_defattrib(int type, int size, int format)
    {
        if(type == ATTRIB_VERTEX)
        {
            glemu_numattribs = glemu_attribmask = 0;
            glemu_vertexsize = 0;
        }
        glemu_changedattribs = true;
        glemu_attribmask |= 1<<type;
        glemu_attribinfo &a = glemu_attribdefs[glemu_numattribs++];
        a.type = type;
        a.size = size;
        a.format = format;
        switch(format)
        {
            case 'B': case GL_UNSIGNED_BYTE:  a.formatsize = 1; a.format = GL_UNSIGNED_BYTE; break;
            case 'b': case GL_BYTE:           a.formatsize = 1; a.format = GL_BYTE; break;
            case 'S': case GL_UNSIGNED_SHORT: a.formatsize = 2; a.format = GL_UNSIGNED_SHORT; break;
            case 's': case GL_SHORT:          a.formatsize = 2; a.format = GL_SHORT; break;
            case 'I': case GL_UNSIGNED_INT:   a.formatsize = 4; a.format = GL_UNSIGNED_INT; break;
            case 'i': case GL_INT:            a.formatsize = 4; a.format = GL_INT; break;
            case 'f': case GL_FLOAT:          a.formatsize = 4; a.format = GL_FLOAT; break;
            case 'd': case GL_DOUBLE:         a.formatsize = 8; a.format = GL_DOUBLE; break;
            default:                          a.formatsize = 0; a.format = GL_FALSE; break;
        }
        a.formatsize *= size;
        a.offset = glemu_vertexsize;
        glemu_vertexsize += a.formatsize;
    }

    void Opengl::Glemu_defattribs(const char *fmt)
    {
        for(;; fmt += 3)
        {
            GLenum format;
            switch(fmt[0])
            {
                case 'v': format = ATTRIB_VERTEX; break;
                case 'c': format = ATTRIB_COLOR; break;
                case 't': format = ATTRIB_TEXCOORD0; break;
                case 'T': format = ATTRIB_TEXCOORD1; break;
                case 'n': format = ATTRIB_NORMAL; break;
                case 'x': format = ATTRIB_TANGENT; break;
                case 'w': format = ATTRIB_BONEWEIGHT; break;
                case 'i': format = ATTRIB_BONEINDEX; break;
                default: return;
            }
            Glemu_defattrib(format, fmt[1]-'0', fmt[2]);
        }
    }

    inline void Opengl::Glemu_setattrib(const glemu_attribinfo &a, unsigned char *buf)
    {
        switch(a.type)
        {
            case ATTRIB_VERTEX:
            case ATTRIB_TEXCOORD0:
            case ATTRIB_TEXCOORD1:
            case ATTRIB_BONEINDEX:
                glVertexAttribPointer_(a.type, a.size, a.format, GL_FALSE, glemu_vertexsize, buf);
                break;
            case ATTRIB_COLOR:
            case ATTRIB_NORMAL:
            case ATTRIB_TANGENT:
            case ATTRIB_BONEWEIGHT:
                glVertexAttribPointer_(a.type, a.size, a.format, GL_TRUE, glemu_vertexsize, buf);
                break;
        }
        if(!(glemu_enabled&(1<<a.type)))
        {
            glEnableVertexAttribArray_(a.type);
            glemu_enabled |= 1<<a.type;
        }
    }

    inline void Opengl::Glemu_unsetattrib(const glemu_attribinfo &a)
    {
        glDisableVertexAttribArray_(a.type);
        glemu_enabled &= ~(1<<a.type);
    }

    inline void Opengl::Glemu_setattribs(unsigned char *buf)
    {
        bool forceattribs = glemu_numattribs != glemu_numlastattribs || glemu_vertexsize != glemu_lastvertexsize || buf != glemu_lastbuf;
        if(forceattribs || glemu_changedattribs)
        {
            int diffmask = glemu_enabled & glemu_lastattribmask & ~glemu_attribmask;
            if(diffmask) {
                for (int i = 0; i < glemu_numlastattribs; ++i) {
                    {
                        const glemu_attribinfo &a = glemu_lastattribs[i];
                        if (diffmask & (1 << a.type)) Glemu_unsetattrib(a);
                    }
                }
            }
            unsigned char *src = buf;
                for(int i=0;i<glemu_numattribs;++i) {
                const glemu_attribinfo &a = glemu_attribdefs[i];
                if(forceattribs || a != glemu_lastattribs[i])
                {
                    Glemu_setattrib(a, src);
                    glemu_lastattribs[i] = a;
                }
                src += a.formatsize;
            }
                glemu_lastbuf = buf;
            glemu_numlastattribs = glemu_numattribs;
            glemu_lastattribmask = glemu_attribmask;
            glemu_lastvertexsize = glemu_vertexsize;
            glemu_changedattribs = false;
        }
    }

    void Opengl::Glemu_multidraw()
    {
        int start = glemu_multidrawstart.empty() ? glemu_multidrawstart.size() + glemu_multidrawcount.size() : 0,
        count = glemu_attribbuf.size()/glemu_vertexsize - start;
        if(count > 0)
        {
            glemu_multidrawstart.resize(start);
            glemu_multidrawcount.resize(count);
        }
    }

    int Opengl::Glemu_end()
    {
        unsigned char *buf = glemu_attribbuf.getbuf();
        if(glemu_attribbuf.empty())
        {
            if(buf != glemu_attribdata)
            {
                glUnmapBuffer_(GL_ARRAY_BUFFER);
                glemu_attribbuf.reset(glemu_attribdata, glemu_maxvboxsize);
            }
            return 0;
        }
        int start = 0;
        if(glversion >= 300)
        {
            if(buf == glemu_attribdata)
            {
                if(glemu_vbooffset + glemu_attribbuf.size() >= glemu_maxvboxsize)
                {
                    if(!glemu_vbo) glGenBuffers_(1, &glemu_vbo);
                    glBindBuffer_(GL_ARRAY_BUFFER, glemu_vbo);
                    glBufferData_(GL_ARRAY_BUFFER, glemu_maxvboxsize, nullptr, GL_STREAM_DRAW);
                    glemu_vbooffset = 0;
                }
                else if(!glemu_lastvertexsize) glBindBuffer_(GL_ARRAY_BUFFER, glemu_vbo);
                void *dst = intel_mapbufferrange_bug ? NULL :
                            glMapBufferRange_(GL_ARRAY_BUFFER, glemu_vbooffset, glemu_attribbuf.length(), GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT|GL_MAP_UNSYNCHRONIZED_BIT);
                if(dst)
                {
                    memcpy(dst, glemu_attribbuf.getbuf(), glemu_attribbuf.size());
                    glUnmapBuffer_(GL_ARRAY_BUFFER);
                }
                else glBufferSubData_(GL_ARRAY_BUFFER, glemu_vbooffset, glemu_attribbuf.size(), glemu_attribbuf.getbuf());
            }
            else glUnmapBuffer_(GL_ARRAY_BUFFER);
            buf = (unsigned char *)0 + glemu_vbooffset;
            if(glemu_vertexsize == glemu_lastvertexsize && buf >= glemu_lastbuf)
            {
                start = int(buf - glemu_lastbuf)/glemu_vertexsize;
                if(glemu_primtype == GL_QUADS && (start%4 || start + glemu_attribbuf.size()/glemu_vertexsize >= 4*glemu_maxquads))
                    start = 0;
                else buf = glemu_lastbuf;
            }
            glemu_vbooffset += glemu_attribbuf.size();
        }
        Glemu_setattribs(buf);
        int numvertexes = glemu_attribbuf.size()/glemu_vertexsize;
        if(glemu_primtype == GL_QUADS)
        {
            if(!glemu_quadsenabled) Glemu_enablequads();
            for(int quads = numvertexes/4;;)
            {
                int count = std::min(quads, static_cast<int>(glemu_maxquads));
                Glemu_drawquads(start/4, count);
                quads -= count;
                if(quads <= 0) break;
                setattribs(buf + 4*count*glemu_vertexsize);
                start = 0;
            }
        }
        else
        {
            if(glemu_multidrawstart.size())
            {
                Glemu_multidraw();
                if(start) {
                    for(int & i : glemu_multidrawstart) {
                        i += start;
                    }
                }
                glMultiDrawArrays_(glemu_primtype, glemu_multidrawstart.getbuf(), glemu_multidrawcount.getbuf(), glemu_multidrawstart.length());
                glemu_multidrawstart.resize(0);
                glemu_multidrawcount.resize(0);
            }
            else glDrawArrays(glemu_primtype, start, numvertexes);
        }
        glemu_attribbuf.reset(glemu_attribdata, glemu_maxvboxsize);
        return numvertexes;
    }

    void Opengl::Glemu_setup()
    {
        if(glversion >= 300)
        {
            if(!glemu_defaultvao) glGenVertexArrays_(1, &glemu_defaultvao);
            glBindVertexArray_(glemu_defaultvao);
        }
        glemu_attribdata = new unsigned char[glemu_maxvboxsize];
        glemu_attribbuf.reset(glemu_attribdata, glemu_maxvboxsize);
    }

    void Opengl::Glemu_forcedisable()
    {
        for(int i = 0; glemu_enabled; i++) if(glemu_enabled&(1<<i)) { glDisableVertexAttribArray_(i); glemu_enabled &= ~(1<<i); }
        glemu_numlastattribs = glemu_lastattribmask = glemu_lastvertexsize = 0;
        glemu_lastbuf = nullptr;
        if(glemu_quadsenabled) Glemu_disablequads();
        if(glversion >= 300) glBindBuffer_(GL_ARRAY_BUFFER, 0);
    }


    void Opengl::Glemu_cleanup()
    {
        Glemu_disable();

        if(glemu_quadindexes) { glDeleteBuffers_(1, &glemu_quadindexes); glemu_quadindexes = 0; }

        if(glemu_vbo) { glDeleteBuffers_(1, &glemu_vbo); glemu_vbo = 0; }
        glemu_vbooffset = glemu_maxvboxsize;

        if(glemu_defaultvao) { glDeleteVertexArrays_(1, &glemu_defaultvao); glemu_defaultvao = 0; }
    }

    inline void Opengl::Glemu_disable() {
        if(glemu_enabled){
            Glemu_forcedisable();
        }
    }

    void Opengl::defvertex(int size, int format) {
        Glemu_defattrib(ATTRIB_VERTEX, size, format);
    }

    void Opengl::defcolor(int size, int format) {
        Glemu_defattrib(ATTRIB_COLOR, size, format);
    }

    void Opengl::deftexcoord0(int size, int format) {
        Glemu_defattrib(ATTRIB_TEXCOORD0, size, format);
    }

    void Opengl::deftexcoord1(int size, int format) {
        Glemu_defattrib(ATTRIB_TEXCOORD1, size, format);
    }

    void Opengl::defnormal(int size, int format) {
        Glemu_defattrib(ATTRIB_NORMAL, size, format);
    }

    void Opengl::deftangent(int size, int format) {
        Glemu_defattrib(ATTRIB_TANGENT, size, format);
    }

    void Opengl::defboneweight(int size, int format) {
        Glemu_defattrib(ATTRIB_BONEWEIGHT, size, format);
    }

    void Opengl::defboneindex(int size, int format) {
        Glemu_defattrib(ATTRIB_BONEINDEX, size, format);
    }



}