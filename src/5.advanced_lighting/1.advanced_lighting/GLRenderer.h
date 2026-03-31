#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
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
    
    // Texture
    unsigned int floorTexture;
    
    // Lighting
    glm::vec3 lightPos;
    
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
    void setBlinn(bool blinn);
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H