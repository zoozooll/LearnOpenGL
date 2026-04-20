#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <glm/glm.hpp>

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer() = default;

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

private:
    GLuint m_shaderProgram;
    GLuint m_vao, m_vbo, m_ebo;
    int m_width;
    int m_height;
};

#endif //GLRENDERER_H
