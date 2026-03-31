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
    void setViewMatrix(const glm::mat4& view);
    
private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    Shader* ourShader;
    int screenWidth, screenHeight;
    
    glm::vec3 cubePositions[10];
    
    void setupShaders();
    void setupBuffers();
    void setupTextures();
};