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

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* asteroidShader;
    Shader* planetShader;
    
    // Camera
    Camera* camera;
    
    // Models
    Model* rock;
    Model* planet;
    
    // Model matrices for instancing
    unsigned int amount;
    glm::mat4* modelMatrices;
    unsigned int instanceVBO;
    
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
};

#endif // GLRENDERER_H