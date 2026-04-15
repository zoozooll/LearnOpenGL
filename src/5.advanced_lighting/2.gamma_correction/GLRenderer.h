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

    // Settings
    bool gammaEnabled;
    bool gammaKeyPressed;

private:
    unsigned int loadTexture(char const * path, bool gammaCorrection);

    Shader* m_pShader;
    unsigned int m_planeVAO;
    unsigned int m_planeVBO;
    unsigned int m_floorTexture;
    unsigned int m_floorTextureGammaCorrected;

    glm::vec3 m_lightPositions[4];
    glm::vec3 m_lightColors[4];
};

#endif //GLRENDERER_H