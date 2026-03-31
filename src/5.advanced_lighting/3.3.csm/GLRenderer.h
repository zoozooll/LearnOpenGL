#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
private:
    // Shader
    Shader* shader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects and Vertex Buffer Objects
    unsigned int cubeVAO, cubeVBO;
    unsigned int planeVAO, planeVBO;
    
    // Textures
    unsigned int cubeTexture;
    unsigned int floorTexture;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Input
    bool keys[1024];
    
    // Helper functions
    unsigned int loadTexture(const char *path);
    
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    
    // Window resize
    void onSizeChanged(int width, int height);
    
    // Input handling
    void processKeyboard(int key, int scancode, int action, int mode);
    void processMouseMovement(double xpos, double ypos);
    void processMouseScroll(double xoffset, double yoffset);
    void doMovement();
    
    // Getters
    Camera* getCamera();
    float getDeltaTime();
    float getLastFrame();
    
    // Setters
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H