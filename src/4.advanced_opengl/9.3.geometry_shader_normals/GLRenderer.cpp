#include "GLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <iostream>

GLRenderer::GLRenderer() : m_pShader(nullptr), m_pNormalShader(nullptr), m_pBackpack(nullptr),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)), lastX(800.0f / 2.0f), lastY(600.0f / 2.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f)
{
}

void GLRenderer::OnInit()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    m_pShader = new Shader("9.3.default.vs", "9.3.default.fs");
    m_pNormalShader = new Shader("9.3.normal_visualization.vs", "9.3.normal_visualization.fs", "9.3.normal_visualization.gs");

    // load models
    // -----------
    stbi_set_flip_vertically_on_load(true);
    m_pBackpack = new Model(FileSystem::getPath("resources/objects/backpack/backpack.obj"));
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    if(m_pShader && m_pNormalShader && m_pBackpack)
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 1.0f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();;
        glm::mat4 model = glm::mat4(1.0f);

        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        m_pShader->setMat4("model", model);

        // draw model as usual
        m_pBackpack->Draw(*m_pShader);

        // then draw model with normal visualizing geometry shader
        m_pNormalShader->use();
        m_pNormalShader->setMat4("projection", projection);
        m_pNormalShader->setMat4("view", view);
        m_pNormalShader->setMat4("model", model);

        m_pBackpack->Draw(*m_pNormalShader);
    }
}

void GLRenderer::OnDestroy()
{
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pNormalShader)
    {
        delete m_pNormalShader;
        m_pNormalShader = nullptr;
    }
    if (m_pBackpack)
    {
        delete m_pBackpack;
        m_pBackpack = nullptr;
    }
}