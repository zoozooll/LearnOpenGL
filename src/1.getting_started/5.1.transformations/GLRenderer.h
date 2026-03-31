#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    unsigned int shaderProgram;
    
    void setupShaders();
    void setupBuffers();
    void setupTextures();
};