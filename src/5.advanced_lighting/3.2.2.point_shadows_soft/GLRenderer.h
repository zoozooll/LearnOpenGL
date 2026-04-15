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

    // Shadow settings
    bool shadows;
    bool shadowsKeyPressed;

private:
    void renderScene(const Shader &shader);
    void renderCube();
    static unsigned int loadTexture(char const * path);

    Shader* m_pShader;
    Shader* m_pSimpleDepthShader;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;

    unsigned int m_woodTexture;
    unsigned int m_depthMapFBO;
    unsigned int m_depthCubemap;

    glm::vec3 m_lightPos;
};

#endif //GLRENDERER_H
