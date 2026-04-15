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
    void renderQuad();
    void renderCube();
    void renderScene(const Shader &shader);
    unsigned int loadTexture(char const * path);

    Shader* m_pShader;
    Shader* m_pSimpleDepthShader;
    Shader* m_pDebugDepthQuad;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_planeVAO;
    unsigned int m_planeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_woodTexture;
    unsigned int m_depthMapFBO;
    unsigned int m_depthMap;
};

#endif //GLRENDERER_H