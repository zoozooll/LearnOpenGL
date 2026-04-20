#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <learnopengl/camera.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shader;

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
    Shader* m_pShader;
    Shader* m_pSkyboxShader;

    unsigned int cubeVAO, cubeVBO;
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int cubemapTexture;

    unsigned int loadTexture(const char *path);
    unsigned int loadCubemap(std::vector<std::string> faces);
};

#endif //GLRENDERER_H