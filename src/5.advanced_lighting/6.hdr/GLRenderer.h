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
    Shader* hdrShader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int quadVAO, quadVBO;
    unsigned int cubeVAO, cubeVBO;
    
    // Textures
    unsigned int woodTexture;
    
    // Framebuffer
    unsigned int hdrFBO;
    unsigned int colorBuffer;
    unsigned int rboDepth;
    
    // Timing
    float deltaTime, lastFrame;
    
    // HDR settings
    bool hdr;
    float exposure;
    
    // Helper functions
    void renderQuad();
    void renderCube();
    unsigned int loadTexture(const char *path, bool gammaCorrection);
    
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
    bool getHDR();
    float getExposure();
    
    // Setters
    void setLastFrame(float frame);
    void setHDR(bool hdr);
    void setExposure(float exposure);
};

#endif // GLRENDERER_H