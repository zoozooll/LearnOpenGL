#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>

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

    Shader* m_pShader;
    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_planeVAO;
    unsigned int m_planeVBO;
    unsigned int m_transparentVAO;
    unsigned int m_transparentVBO;

    unsigned int m_cubeTexture;
    unsigned int m_floorTexture;
    unsigned int m_transparentTexture;

    std::vector<glm::vec3> m_windows;
};

#endif //GLRENDERER_H