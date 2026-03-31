#include "GLRenderer.h"

#include <iostream>

int width, height;

GLRenderer::GLRenderer() {
}

GLRenderer::~GLRenderer() {
    // Cleanup resources
    cleanup();
    
    // Delete dynamically allocated objects
    delete shader;
}

void GLRenderer::initialize() {
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // Build and compile shader with geometry shader
    shader = new Shader("9.1.geometry_shader.vs", "9.1.geometry_shader.fs", "9.1.geometry_shader.gs");
    
    // Set up vertex data and configure vertex attributes
    float points[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };
    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void GLRenderer::render() {
    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw points
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 4);
    glBindVertexArray(0);
}

void GLRenderer::cleanup() {
    // De-allocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GLRenderer::onSizeChanged(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}