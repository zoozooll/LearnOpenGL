#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
private:
    Shader* shader;
    Camera* camera;
    unsigned int cubeVAO, cubeVBO;

public:
    GLRenderer();
    virtual ~GLRenderer();

    void initialize();
    void render(float deltaTime);
    void cleanup();
    void onSizeChanged(int width, int height);
};