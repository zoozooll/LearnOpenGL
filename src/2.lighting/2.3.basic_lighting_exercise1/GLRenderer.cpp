#include "GLRenderer.h"
#include <iostream>
#include <learnopengl/filesystem.h>

int width, height;

GLRenderer::GLRenderer() : 
    lightingShader(nullptr),
    lightCubeShader(nullptr),
    camera(nullptr),
    cubeVAO(0),
    lightCubeVAO(0),
    VBO(0),
    lightPos(glm::vec3(1.2f, 1.0f, 2.0f))
{}

GLRenderer::~GLRenderer() {
    cleanup();
    if (lightingShader) {
        delete lightingShader;
    }
    if (lightCubeShader) {
        delete lightCubeShader;
    }
    if (camera) {
        delete camera;
    }
}

void GLRenderer::initialize() {
    // initialize camera
    if (!camera) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    }
    
    setupShaders();
    setupBuffers();
}

void GLRenderer::render() {
    // Clear the colorbuffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Create camera transformations
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 100.0f);

    // Use lighting shader
    lightingShader->use();

    // Set uniforms for lighting
    lightingShader->setVec3("lightPos", lightPos);
    lightingShader->setVec3("viewPos", camera->Position);

    // Set light properties
    lightingShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // Set material properties
    lightingShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    lightingShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    lightingShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    lightingShader->setFloat("material.shininess", 32.0f);

    // Set view and projection matrices
    lightingShader->setMat4("view", view);
    lightingShader->setMat4("projection", projection);

    // Draw the cube
    glBindVertexArray(cubeVAO);
    glm::mat4 model = glm::mat4(1.0f);
    lightingShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw the light source
    lightCubeShader->use();
    lightCubeShader->setMat4("view", view);
    lightCubeShader->setMat4("projection", projection);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader->setMat4("model", model);
    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void GLRenderer::cleanup() {
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}



Camera* GLRenderer::getCamera() {
    return camera;
}

void GLRenderer::setupShaders() {
    // Create and compile shaders
    lightingShader = new Shader("2.2.basic_lighting.vs", "2.2.basic_lighting.fs");
    lightCubeShader = new Shader("2.2.light_cube.vs", "2.2.light_cube.fs");
}

void GLRenderer::setupBuffers() {
    // Cube vertices with normals
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // Create VBO and VAOs
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Cube VAO
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Light cube VAO
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}