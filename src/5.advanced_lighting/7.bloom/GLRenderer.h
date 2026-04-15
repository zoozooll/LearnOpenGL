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

    // Bloom settings
    bool bloom;
    bool bloomKeyPressed;
    float exposure;

private:
    void renderQuad();
    void renderCube();
    unsigned int loadTexture(char const * path, bool gammaCorrection);

    Shader* m_pShader;
    Shader* m_pShaderLight;
    Shader* m_pShaderBlur;
    Shader* m_pShaderBloomFinal;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_woodTexture;
    unsigned int m_containerTexture;

    unsigned int m_hdrFBO;
    unsigned int m_colorBuffers[2];
    unsigned int m_rboDepth;

    unsigned int m_pingpongFBO[2];
    unsigned int m_pingpongColorbuffers[2];

    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
};

#endif //GLRENDERER_H