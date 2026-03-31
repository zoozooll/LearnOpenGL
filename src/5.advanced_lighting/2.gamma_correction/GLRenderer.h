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
    // Shader
    Shader* shader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Object and Vertex Buffer Object
    unsigned int planeVAO, planeVBO;
    
    // Textures
    unsigned int floorTexture;
    unsigned int floorTextureGammaCorrected;
    
    // Lighting
    glm::vec3 lightPositions[4];
    glm::vec3 lightColors[4];
    
    // Timing
    float deltaTime, lastFrame;
    
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
    void setGamma(bool gamma);
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H