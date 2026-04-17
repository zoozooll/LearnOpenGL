#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>

class GLRenderer {
public:
    GLRenderer() = default;
    virtual ~GLRenderer() = default;

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();
};

#endif
