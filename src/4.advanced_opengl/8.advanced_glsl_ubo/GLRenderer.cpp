#include "GLRenderer.h"

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
    delete shaderRed;
    delete shaderGreen;
    delete shaderBlue;
    delete shaderYellow;
    delete camera;
}

void GLRenderer::initialize() {
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // Build and compile shaders
    shaderRed = new Shader("8.advanced_glsl.vs", "8.red.fs");
    shaderGreen = new Shader("8.advanced_glsl.vs", "8.green.fs");
    shaderBlue = new Shader("8.advanced_glsl.vs", "8.blue.fs");
    shaderYellow = new Shader("8.advanced_glsl.vs", "8.yellow.fs");
    
    // Set up vertex data and configure vertex attributes
    float cubeVertices[] = {
        // positions         
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };
    
    // Cube VAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    // Configure a uniform buffer object
    // First, get the relevant block indices
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed->ID, "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen->ID, "Matrices");
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue->ID, "Matrices");
    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow->ID, "Matrices");
    
    // Then link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(shaderRed->ID, uniformBlockIndexRed, 0);
    glUniformBlockBinding(shaderGreen->ID, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(shaderBlue->ID, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(shaderYellow->ID, uniformBlockIndexYellow, 0);
    
    // Now actually create the buffer
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    
    // Store the projection matrix (we only do this once now)
    glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLRenderer::render() {
    // Per-frame time logic
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set the view matrix in the uniform block
    glm::mat4 view = camera->GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    // Draw 4 cubes
    glBindVertexArray(cubeVAO);
    
    // RED
    shaderRed->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // Move top-left
    shaderRed->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // GREEN
    shaderGreen->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // Move top-right
    shaderGreen->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // YELLOW
    shaderYellow->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // Move bottom-left
    shaderYellow->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // BLUE
    shaderBlue->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // Move bottom-right
    shaderBlue->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
}

void GLRenderer::cleanup() {
    // De-allocate all resources
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &uboMatrices);
}

void GLRenderer::onSizeChanged(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    
    // Update projection matrix in UBO
    glm::mat4 projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Camera* GLRenderer::getCamera() {
    return camera;
}

float GLRenderer::getDeltaTime() {
    return deltaTime;
}