#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/camera.h>

class Shader;

extern int width, height;

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();

    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);

    Camera* camera;

private:
    // Shader program IDs
    Shader* lightingShader;
    Shader* lightCubeShader;

    // Vertex array objects
    unsigned int cubeVAO, lightCubeVAO;

    // Vertex buffer objects
    unsigned int VBO;

    // Textures
    unsigned int diffuseMap, specularMap;

    // Cube positions
    glm::vec3 cubePositions[10];

    void setupShaders();
    void setupBuffers();
    void loadTextures();
    unsigned int loadTexture(const char *path);
};

#endif // GL_RENDERER_H