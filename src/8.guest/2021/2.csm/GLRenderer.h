#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <vector>
#include <random>

class Shader;

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer();

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;
    float cameraNearPlane;
    float cameraFarPlane;

    // Timing
    float deltaTime;
    float lastFrame;

    std::vector<float> shadowCascadeLevels;
    int debugLayer;
    bool showQuad;
    std::vector<glm::mat4> lightMatricesCache;

private:
    Shader* shader;
    Shader* simpleDepthShader;
    Shader* debugDepthQuad;
    Shader* debugCascadeShader;

    unsigned int planeVAO, planeVBO;
    unsigned int cubeVAO, cubeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int woodTexture;
    unsigned int lightFBO;
    unsigned int lightDepthMaps;
    unsigned int matricesUBO;

    int m_width;
    int m_height;

    std::mt19937 generator;

    void renderScene(const Shader &shader);
    void renderCube();
    void renderQuad();
    std::vector<glm::mat4> getLightSpaceMatrices();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& projview);
    void drawCascadeVolumeVisualizers(const std::vector<glm::mat4>& lightMatrices, Shader* shader);
    unsigned int loadTexture(const char *path);
};

#endif //GLRENDERER_H
