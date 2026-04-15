#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>

class Shader; // Forward declaration

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

    // Timing
    float deltaTime;
    float lastFrame;

private:
    Shader* solidShader;
    Shader* transparentShader;
    Shader* compositeShader;
    Shader* screenShader;

    unsigned int quadVAO, quadVBO;
    unsigned int opaqueFBO, transparentFBO;
    unsigned int opaqueTexture;
    unsigned int depthTexture;
    unsigned int accumTexture;
    unsigned int revealTexture;

    int m_width;
    int m_height;

    glm::mat4 calculate_model_matrix(const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
};

#endif //GLRENDERER_H
