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

#include <vector>
#include <map>
#include <iostream>

class GLRenderer
{
private:
    // Shaders
    Shader* shader;
    
    // Camera
    Camera* camera;
    
    // Textures
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned int transparentTexture;
    
    // VAOs and VBOs
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    unsigned int transparentVAO, transparentVBO;
    
    // Window positions
    std::vector<glm::vec3> windows;
    
public:
    GLRenderer();
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
    void setupWindows();
    unsigned int loadTexture(const char* path);
};