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
    // Shaders
    Shader* shader;
    Shader* simpleDepthShader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int cubeVAO, cubeVBO;
    
    // Texture
    unsigned int woodTexture;
    
    // Depth map
    unsigned int depthMapFBO;
    unsigned int depthCubemap;
    const unsigned int SHADOW_WIDTH;
    const unsigned int SHADOW_HEIGHT;
    
    // Lighting
    glm::vec3 lightPos;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Shadows toggle
    bool shadows;
    bool shadowsKeyPressed;
    
    // Helper functions
    void renderScene(const Shader &shader);
    void renderCube();
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
    bool getShadows();
    
    // Setters
    void setLastFrame(float frame);
    void setShadows(bool shadows);
    void toggleShadows();
};

#endif // GLRENDERER_H