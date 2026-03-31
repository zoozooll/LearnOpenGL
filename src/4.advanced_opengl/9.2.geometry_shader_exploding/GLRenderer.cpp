#include "GLRenderer.h"

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
    delete camera;
    delete nanosuit;
}

void GLRenderer::initialize() {
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // Build and compile shader with geometry shader
    shader = new Shader("9.2.geometry_shader.vs", "9.2.geometry_shader.fs", "9.2.geometry_shader.gs");
    
    // Load model
    nanosuit = new Model(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
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
    
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
    
    // Add time component to geometry shader in the form of a uniform
    shader->setFloat("time", static_cast<float>(glfwGetTime()));
    
    // Draw model
    nanosuit->Draw(*shader);
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