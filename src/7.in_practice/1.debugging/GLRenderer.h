#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader; // Forward declaration

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
    Shader* m_pShader;
    unsigned int m_cubeVAO, m_cubeVBO;
    unsigned int m_texture;
    int m_width;
    int m_height;

    static void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
                                     GLsizei length, const char *message, const void *userParam);
};

#endif //GLRENDERER_H
