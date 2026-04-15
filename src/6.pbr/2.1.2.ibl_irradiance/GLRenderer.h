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
    Shader* pbrShader;
    Shader* equirectangularToCubemapShader;
    Shader* irradianceShader;
    Shader* backgroundShader;

    unsigned int sphereVAO = 0;
    unsigned int indexCount;
    void renderSphere();

    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    void renderCube();

    unsigned int captureFBO;
    unsigned int captureRBO;
    unsigned int hdrTexture;
    unsigned int envCubemap;
    unsigned int irradianceMap;

    glm::vec3 lightPositions[4];
    glm::vec3 lightColors[4];
    int nrRows;
    int nrColumns;
    float spacing;

    int m_width;
    int m_height;
};

#endif //GLRENDERER_H
