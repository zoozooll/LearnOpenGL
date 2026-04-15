#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

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
    unsigned int loadCubemap(std::vector<std::string> faces);

    Shader* m_pShader;
    Shader* m_pSkyboxShader;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_skyboxVAO;
    unsigned int m_skyboxVBO;

    unsigned int m_cubeTexture;
    unsigned int m_cubemapTexture;
};

#endif //GLRENDERER_H