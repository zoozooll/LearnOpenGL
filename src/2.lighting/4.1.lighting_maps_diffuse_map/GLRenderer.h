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
    unsigned int loadTexture(char const * path);

    Shader* m_pLightingShader;
    Shader* m_pLightCubeShader;
    unsigned int m_cubeVAO;
    unsigned int m_lightCubeVAO;
    unsigned int m_VBO;
    unsigned int m_diffuseMap;
    glm::vec3 m_lightPos;
};

#endif //GLRENDERER_H