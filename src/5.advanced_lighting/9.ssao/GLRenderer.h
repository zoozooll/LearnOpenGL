#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <vector>

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* shaderGeometryPass;
    Shader* shaderLightingPass;
    Shader* shaderSSAO;
    Shader* shaderSSAOBlur;
    
    // Camera
    Camera* camera;
    
    // Model
    Model* backpack;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int quadVAO, quadVBO;
    unsigned int cubeVAO, cubeVBO;
    
    // Framebuffers
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedo;
    unsigned int rboDepth;
    
    // SSAO framebuffers
    unsigned int ssaoFBO, ssaoBlurFBO;
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
    
    // Noise texture
    unsigned int noiseTexture;
    
    // SSAO kernel
    std::vector<glm::vec3> ssaoKernel;
    std::vector<glm::vec3> ssaoNoise;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Lighting
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    
    // Helper functions
    void renderQuad();
    void renderCube();
    float ourLerp(float a, float b, float f);
    
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