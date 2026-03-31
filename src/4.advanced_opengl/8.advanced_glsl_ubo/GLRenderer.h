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
    // Shaders
    Shader* shaderRed;
    Shader* shaderGreen;
    Shader* shaderBlue;
    Shader* shaderYellow;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int cubeVAO, cubeVBO;
    
    // Uniform Buffer Object
    unsigned int uboMatrices;
    
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