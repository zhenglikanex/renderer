#ifndef GLSUPPORT_H_
#define GLSUPPORT_H_

#include "glad/glad.h"

#define ENABLE_GL_CHECK 1

#if ENABLE_GL_CHECK
#include "StringUtil.h"
#include "LogManager.h"
#define CHECK_GL_ERROR(glFunc) \
{ \
    glFunc; \
    int e = glGetError(); \
    if (e != 0) \
    { \
        std::string error_string; \
        switch(e) \
        { \
            case GL_INVALID_ENUM:       error_string = "GL_INVALID_ENUM";        break; \
            case GL_INVALID_VALUE:      error_string = "GL_INVALID_VALUE";       break; \
            case GL_INVALID_OPERATION:  error_string = "GL_INVALID_OPERATION";   break; \
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error_string = "GL_INVALID_FRAMEBUFFER_OPERATION";   break; \
            case GL_OUT_OF_MEMORY:      error_string = "GL_OUT_OF_MEMORY";       break; \
            default:                                                            break; \
        } \
        char msgBuf[4096]; \
        auto tokens = StringUtil::split(#glFunc, '('); \
        sprintf_s(msgBuf, "OpenGL error 0x%04X %s in %s at line %i for %s\n", e, error_string.c_str(), __FUNCTION__, __LINE__, tokens[0].c_str()); \
		LOG_ERROR() << msgBuf << LOG_END(); \
    } \
}
#else
#   define CHECK_GL_ERROR(glFunc) { glFunc; }
#endif

#endif
