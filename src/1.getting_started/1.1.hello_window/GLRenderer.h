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
    // OpenGL相关状态
};