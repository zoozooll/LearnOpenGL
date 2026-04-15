#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
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

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

private:
    Shader* m_pShader;
    Shader* m_pScreenShader;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_framebuffer;
    unsigned int m_textureColorBufferMultiSampled;
    unsigned int m_rbo;

    unsigned int m_intermediateFBO;
    unsigned int m_screenTexture;
};

#endif //GLRENDERER_H