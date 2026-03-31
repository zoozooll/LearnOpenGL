#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

class GLRenderer {
private:
    // Shaders
    Shader* lightingShader;
    Shader* lightCubeShader;

    // Vertex Array Objects and Buffers
    unsigned int VBO, cubeVAO, lightCubeVAO;

    // Textures
    unsigned int diffuseMap;

    // Lighting
    glm::vec3 lightPos;

    // Camera
    Camera* camera;

    // Window dimensions
    int screenWidth, screenHeight;

public:
    // Constructor
    GLRenderer();

    // Destructor
    ~GLRenderer();

    // Lifecycle methods
    void initialize();
    void render();
    void cleanup();

    // Window resize handler
    void onSizeChanged(int width, int height);
    
    // Camera accessor
    Camera* getCamera();

private:
    // Texture loading utility
    unsigned int loadTexture(const char *path);
};

#endif // GLRENDERER_H