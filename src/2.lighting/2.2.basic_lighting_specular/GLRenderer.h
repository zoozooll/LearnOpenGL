#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
    // camera accessor
    Camera* getCamera();
    
private:
    unsigned int VBO, cubeVAO, lightCubeVAO;
    Shader* lightingShader;
    Shader* lightCubeShader;
    int screenWidth, screenHeight;
    
    // camera
    Camera* camera;
    
    // lighting
    glm::vec3 lightPos;
    
    void setupShaders();
    void setupBuffers();
};