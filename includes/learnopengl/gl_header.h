#ifndef GL_HEADER_H
#define GL_HEADER_H

#ifdef __ANDROID__
    #include <GLES3/gl32.h>
    #include <GLES3/gl3ext.h>
#else
    #include <glad/glad.h>
#endif

#endif
