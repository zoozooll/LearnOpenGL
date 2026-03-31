#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <vector>

extern int width, height;

class GLRenderer {
private:
    // Shader
    Shader* shader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Object for sphere
    unsigned int sphereVAO;
    unsigned int indexCount;
    
    // Textures
    unsigned int albedo;
    unsigned int normal;
    unsigned int metallic;
    unsigned int roughness;
    unsigned int ao;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Lights
    glm::vec3 lightPositions[1];
    glm::vec3 lightColors[1];
    int nrRows, nrColumns;
    float spacing;
    
    // Helper functions
    void renderSphere();
    unsigned int loadTexture(const char *path);
    
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
    float getLastFrame();
    
    // Setters
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H