#include "GLRenderer.h"

#include <learnopengl/filesystem.h>
#include <iostream>

int width, height;

GLRenderer::GLRenderer() : deltaTime(0.0f), lastFrame(0.0f), amount(100000) {
    
    // Initialize camera
    camera = new Camera(glm::vec3(0.0f, 0.0f, 155.0f));
    
    // Allocate memory for model matrices
    modelMatrices = new glm::mat4[amount];
}

GLRenderer::~GLRenderer() {
    // Cleanup resources
    cleanup();
    
    // Delete dynamically allocated objects
    delete asteroidShader;
    delete planetShader;
    delete camera;
    delete rock;
    delete planet;
    delete[] modelMatrices;
}

void GLRenderer::initialize() {
    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);
    
    // Build and compile shaders
    asteroidShader = new Shader("10.3.asteroids.vs", "10.3.asteroids.fs");
    planetShader = new Shader("10.3.planet.vs", "10.3.planet.fs");
    
    // Load models
    rock = new Model(FileSystem::getPath("resources/objects/rock/rock.obj"));
    planet = new Model(FileSystem::getPath("resources/objects/planet/planet.obj"));
    
    // Generate a large list of semi-random model transformation matrices
    srand(static_cast<unsigned int>(glfwGetTime())); // Initialize random seed
    float radius = 150.0;
    float offset = 25.0f;
    for (unsigned int i = 0; i < amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)amount * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }
    
    // Configure instanced array
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    
    // Set transformation matrices as an instance vertex attribute (with divisor 1)
    for (unsigned int i = 0; i < rock->meshes.size(); i++) {
        unsigned int VAO = rock->meshes[i].VAO;
        glBindVertexArray(VAO);
        // Set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
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
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
    glm::mat4 view = camera->GetViewMatrix();
    
    asteroidShader->use();
    asteroidShader->setMat4("projection", projection);
    asteroidShader->setMat4("view", view);
    
    planetShader->use();
    planetShader->setMat4("projection", projection);
    planetShader->setMat4("view", view);
    
    // Draw planet
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    planetShader->setMat4("model", model);
    planet->Draw(*planetShader);
    
    // Draw meteorites
    asteroidShader->use();
    asteroidShader->setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rock->textures_loaded[0].id); // Note: we assume the model class has a public textures_loaded vector
    
    for (unsigned int i = 0; i < rock->meshes.size(); i++) {
        glBindVertexArray(rock->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock->meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
        glBindVertexArray(0);
    }
}

void GLRenderer::cleanup() {
    // De-allocate instance VBO
    glDeleteBuffers(1, &instanceVBO);
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