#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

extern int width, height;

class GLRenderer {
private:
    Shader* shader;
    Shader* screenShader;
    Camera* camera;
    unsigned int cubeVAO, cubeVBO;
    unsigned int quadVAO, quadVBO;
    unsigned int framebuffer;
    unsigned int textureColorBufferMultiSampled;
    unsigned int rbo;
    unsigned int intermediateFBO;
    unsigned int screenTexture;

public:
    GLRenderer();
    ~GLRenderer();

    void initialize();
    void render(float deltaTime);
    void cleanup();
    void onSizeChanged(int width, int height);
};