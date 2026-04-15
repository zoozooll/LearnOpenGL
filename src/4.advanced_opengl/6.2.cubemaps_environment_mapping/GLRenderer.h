#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

    void ProcessInput(GLFWwindow *window);
    void MouseCallback(double xposIn, double yposIn);
    void ScrollCallback(double xoffset, double yoffset);

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

    int scrWidth;
    int scrHeight;

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