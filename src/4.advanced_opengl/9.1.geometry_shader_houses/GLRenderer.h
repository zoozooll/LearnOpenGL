#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader.h>

extern int width, height;

class GLRenderer {
private:
    // Shader
    Shader* shader;
    
    // Vertex Array Object and Vertex Buffer Object
    unsigned int VAO, VBO;
    
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