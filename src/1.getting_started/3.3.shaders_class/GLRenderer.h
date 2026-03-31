#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
private:
    unsigned int VBO, VAO;
    Shader* ourShader;
    
    void setupShaders();
    void setupBuffers();
};