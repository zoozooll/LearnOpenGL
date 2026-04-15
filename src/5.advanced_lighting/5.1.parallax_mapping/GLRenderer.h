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

    // Parallax
    float heightScale;

private:
    void renderQuad();
    unsigned int loadTexture(char const * path);

    Shader* m_pShader;
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;

    unsigned int m_diffuseMap;
    unsigned int m_normalMap;
    unsigned int m_heightMap;

    glm::vec3 m_lightPos;
};

#endif //GLRENDERER_H