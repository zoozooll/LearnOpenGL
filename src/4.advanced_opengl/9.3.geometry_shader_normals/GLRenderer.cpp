#include "GLRenderer.h"

#include <stb_image.h>
#include <learnopengl/filesystem.h>
#include <iostream>

int width, height;

GLRenderer::GLRenderer() : deltaTime(0.0f), lastFrame(0.0f) {
    
    // Initialize camera
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

GLRenderer::~GLRenderer() {
    // Cleanup resources
    cleanup();
    
    // Delete dynamically allocated objects
    delete shader;
    delete normalShader;
    delete camera;
    delete backpack;
}

void GLRenderer::initialize() {
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // Build and compile shaders
    shader = new Shader("9.3.default.vs", "9.3.default.fs");
    normalShader = new Shader("9.3.normal_visualization.vs", "9.3.normal_visualization.fs", "9.3.normal_visualization.gs");
    
    // Load model
    stbi_set_flip_vertically_on_load(true);
    backpack = new Model(FileSystem::getPath("resources/objects/backpack/backpack.obj"));
}

void GLRenderer::render() {
    // Per-frame time logic
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Configure transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 1.0f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    
    // Draw model as usual
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
    backpack->Draw(*shader);
    
    // Then draw model with normal visualizing geometry shader
    normalShader->use();
    normalShader->setMat4("projection", projection);
    normalShader->setMat4("view", view);
    normalShader->setMat4("model", model);
    backpack->Draw(*normalShader);
}

void GLRenderer::cleanup() {
    // No specific cleanup needed for the model
}

void GLRenderer::onSizeChanged(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

Camera* GLRenderer::getCamera() {
    return camera;
}

float GLRenderer::getDeltaTime() {
    return deltaTime;
}