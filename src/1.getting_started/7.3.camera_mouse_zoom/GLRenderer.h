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
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
private:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;
    Shader* ourShader;
    int screenWidth, screenHeight;
    
    // camera
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    
    // mouse
    bool firstMouse;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
    float fov;
    
    // timing
    float deltaTime;
    float lastFrame;
    
    glm::vec3 cubePositions[10];
    
    void setupShaders();
    void setupBuffers();
    void setupTextures();
};