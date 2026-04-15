#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
#include <learnopengl/model.h>
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

private:
    void renderQuad();
    void renderCube();
    float ourLerp(float a, float b, float f);

    Shader* m_pShaderGeometryPass;
    Shader* m_pShaderLightingPass;
    Shader* m_pShaderSSAO;
    Shader* m_pShaderSSAOBlur;

    Model* m_pBackpack;

    unsigned int m_gBuffer;
    unsigned int m_gPosition, m_gNormal, m_gAlbedo;
    unsigned int m_ssaoFBO, m_ssaoBlurFBO;
    unsigned int m_ssaoColorBuffer, m_ssaoColorBufferBlur;
    unsigned int m_rboDepth;

    std::vector<glm::vec3> m_ssaoKernel;
    unsigned int m_noiseTexture;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    glm::vec3 m_lightPos;
    glm::vec3 m_lightColor;
};

#endif //GLRENDERER_H