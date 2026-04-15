#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader;
class ComputeShader;

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
    Shader* m_screenQuadShader;
    ComputeShader* m_computeShader;
    unsigned int m_texture;
    unsigned int m_quadVAO, m_quadVBO;
    int m_width;
    int m_height;
    int m_fCounter;
    float m_deltaTime;
    float m_lastFrame;

    void renderQuad();
};

#endif //GLRENDERER_H
