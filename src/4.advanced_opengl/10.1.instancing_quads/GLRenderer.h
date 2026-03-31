#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <learnopengl/shader.h>

extern int width, height;

class GLRenderer {
private:
    // Shader
    Shader* shader;
    
    // Vertex Array Object and Vertex Buffer Objects
    unsigned int quadVAO, quadVBO, instanceVBO;
    
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    
    // Window resize
    void onSizeChanged(int width, int height);
};

#endif // GLRENDERER_H