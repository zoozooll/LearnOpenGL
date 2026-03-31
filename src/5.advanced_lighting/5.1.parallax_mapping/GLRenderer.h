#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
private:
    // Shader
    Shader* shader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int quadVAO, quadVBO;
    
    // Textures
    unsigned int diffuseMap;
    unsigned int normalMap;
    unsigned int heightMap;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Lighting
    glm::vec3 lightPos;
    
    // Parallax mapping
    float heightScale;
    
    // Helper functions
    void renderQuad();
    unsigned int loadTexture(const char *path);
    
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    
    // Window resize
    void onSizeChanged(int width, int height);
    
    // Getters
    Camera* getCamera();
    float getDeltaTime();
    float getLastFrame();
    float getHeightScale();
    
    // Setters
    void setLastFrame(float frame);
    void setHeightScale(float scale);
};

#endif // GLRENDERER_H