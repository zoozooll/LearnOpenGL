#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLRenderer {
public:
    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();
};

#endif
