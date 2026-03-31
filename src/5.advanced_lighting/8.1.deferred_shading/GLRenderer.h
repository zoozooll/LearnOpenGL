#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* shaderGeometryPass;
    Shader* shaderLightingPass;
    Shader* shaderLightBox;
    
    // Camera
    Camera* camera;
    
    // Model
    Model* backpack;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int quadVAO, quadVBO;
    unsigned int cubeVAO, cubeVBO;
    
    // Framebuffers
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedoSpec;
    unsigned int rboDepth;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Objects
    std::vector<glm::vec3> objectPositions;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    
    // Helper functions
    void renderQuad();
    void renderCube();
    
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
    
    // Setters
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H