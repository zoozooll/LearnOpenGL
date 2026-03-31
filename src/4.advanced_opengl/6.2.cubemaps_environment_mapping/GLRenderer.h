#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <string>
#include <vector>

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* shader;
    Shader* skyboxShader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int cubeVAO, cubeVBO;
    unsigned int skyboxVAO, skyboxVBO;
    
    // Textures
    unsigned int cubemapTexture;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Texture loading functions
    unsigned int loadCubemap(std::vector<std::string> faces);
    
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    
    // Window resize
    void onSizeChanged(int width, int height);
    
    // Getters
    Camera* getCamera();
    float getDeltaTime();
};

#endif // GLRENDERER_H