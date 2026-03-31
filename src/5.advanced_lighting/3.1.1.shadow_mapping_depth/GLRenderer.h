#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* simpleDepthShader;
    Shader* debugDepthQuad;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int planeVAO, planeVBO;
    unsigned int cubeVAO, cubeVBO;
    unsigned int quadVAO, quadVBO;
    
    // Texture
    unsigned int woodTexture;
    
    // Depth map
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH;
    const unsigned int SHADOW_HEIGHT;
    
    // Lighting
    glm::vec3 lightPos;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Helper functions
    void renderScene(const Shader &shader);
    void renderCube();
    void renderQuad();
    
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