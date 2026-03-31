#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader_m.h>

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
private:
    unsigned int VBO, VAO, EBO;
    unsigned int texture1, texture2;
    Shader* ourShader;
    int screenWidth, screenHeight;
    
    void setupShaders();
    void setupBuffers();
    void setupTextures();
};