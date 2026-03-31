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
    
    // Camera accessor
    Camera* getCamera();

private:
    // Shaders
    Shader* shader;
    Shader* shaderSingleColor;

    // Vertex array objects
    unsigned int cubeVAO, planeVAO;

    // Vertex buffer objects
    unsigned int cubeVBO, planeVBO;

    // Textures
    unsigned int cubeTexture, floorTexture;

    // Camera
    Camera* camera;

    void setupShaders();
    void setupBuffers();
    void loadTextures();
    unsigned int loadTexture(const char *path);
};

#endif // GL_RENDERER_H