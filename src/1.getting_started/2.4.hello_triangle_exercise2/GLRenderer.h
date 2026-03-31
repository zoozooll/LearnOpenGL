#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLRenderer {
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
private:
    unsigned int VBOs[2], VAOs[2];
    unsigned int vertexShader, fragmentShader, shaderProgram;
    
    void setupShaders();
    void setupBuffers();
};