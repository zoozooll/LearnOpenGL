#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();

    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
    // camera accessor
    Camera* getCamera();

    glm::vec3 lightPos;

private:
    // Shaders
    Shader* lightingShader;
    Shader* lightCubeShader;

    // Vertex array objects
    unsigned int cubeVAO, lightCubeVAO;

    // Vertex buffer objects
    unsigned int VBO;

    // Camera
    Camera* camera;

    void setupShaders();
    void setupBuffers();
};

#endif // GL_RENDERER_H