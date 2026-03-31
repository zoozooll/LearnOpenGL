#include "GLRenderer.h"
#include <iostream>
#include <glad/glad.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>

// GLRenderer implementation
GLRenderer::GLRenderer() :
    ourShader(nullptr),
    ourModel(nullptr),
    camera(nullptr)
{
}

GLRenderer::~GLRenderer() {
    cleanup();
    if (ourShader) {
        delete ourShader;
    }
    if (ourModel) {
        delete ourModel;
    }
    if (camera) {
        delete camera;
    }
}

void GLRenderer::initialize() {
    // Initialize camera
    if (!camera) {
        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    }
    
    // Configure global opengl state
    glEnable(GL_DEPTH_TEST);
    
    // Tell stb_image.h to flip loaded texture's on the y-axis
    //stbi_set_flip_vertically_on_load(true);
    
    setupShaders();
    loadModel();
}

void GLRenderer::render() {
    // Clear the colorbuffer
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader
    ourShader->use();

    // View/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);

    // Render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));    // it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    ourModel->Draw(*ourShader);
}

void GLRenderer::cleanup() {
    // Model cleanup is handled by the Model class destructor
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}



Camera* GLRenderer::getCamera() {
    return camera;
}

void GLRenderer::setupShaders() {
    // Create shader
    ourShader = new Shader("1.model_loading.vs", "1.model_loading.fs");
}

void GLRenderer::loadModel() {
    // Load model
    ourModel = new Model(FileSystem::getPath("resources/objects/backpack/backpack.obj"));
}