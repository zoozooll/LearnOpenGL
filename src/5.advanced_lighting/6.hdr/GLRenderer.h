#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
#include <glm/glm.hpp>
#include <vector>

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

    // HDR settings
    bool hdr;
    bool hdrKeyPressed;
    float exposure;

private:
    void renderQuad();
    void renderCube();
    unsigned int loadTexture(char const * path, bool gammaCorrection);

    Shader* m_pShader;
    Shader* m_pHdrShader;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_woodTexture;
    unsigned int m_hdrFBO;
    unsigned int m_colorBuffer;
    unsigned int m_rboDepth;

    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
};

#endif //GLRENDERER_H