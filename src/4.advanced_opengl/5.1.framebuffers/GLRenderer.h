#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <iostream>

class GLRenderer
{
private:
    // Shaders
    Shader* shader;
    Shader* screenShader;
    
    // Camera
    Camera* camera;
    
    // Textures
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned int textureColorbuffer;
    
    // VAOs and VBOs
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int quadVAO, quadVBO;
    
    // Framebuffer
    unsigned int framebuffer;
    unsigned int rbo;
    
    // Window size
    unsigned int screenWidth;
    unsigned int screenHeight;
    
public:
    GLRenderer(unsigned int width, unsigned int height);
    ~GLRenderer();
    
    bool initialize();
    void render(float deltaTime);
    void onSizeChanged(int width, int height);
    
    // Camera accessor
    Camera* getCamera();
    
private:
    bool setupShaders();
    bool setupGeometry();
    bool setupTextures();
    bool setupFramebuffer();
    unsigned int loadTexture(const char* path);
};