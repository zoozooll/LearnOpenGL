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

    Shader* m_pShaderGeometryPass;
    Shader* m_pShaderLightingPass;
    Shader* m_pShaderLightBox;

    Model* m_pBackpack;
    std::vector<glm::vec3> m_objectPositions;

    unsigned int m_gBuffer;
    unsigned int m_gPosition, m_gNormal, m_gAlbedoSpec;
    unsigned int m_rboDepth;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    std::vector<glm::vec3> m_lightPositions;
    std::vector<glm::vec3> m_lightColors;
};

#endif //GLRENDERER_H