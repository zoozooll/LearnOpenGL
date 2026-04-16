#include "GLRenderer.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/time_utils.h>
#include <iostream>

GLRenderer::GLRenderer() : m_pShader(nullptr), m_pNanosuit(nullptr),
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
    m_pShader = new Shader("9.2.geometry_shader.vs", "9.2.geometry_shader.fs", "9.2.geometry_shader.gs");

    // load models
    // -----------
    m_pNanosuit = new Model(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(TimeUtils::GetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    if(m_pShader && m_pNanosuit)
    {
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 1.0f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();;
        glm::mat4 model = glm::mat4(1.0f);
        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);
        m_pShader->setMat4("model", model);

        // add time component to geometry shader in the form of a uniform
        m_pShader->setFloat("time", static_cast<float>(TimeUtils::GetTime()));

        // draw model
        m_pNanosuit->Draw(*m_pShader);
    }
}

void GLRenderer::OnDestroy()
{
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pNanosuit)
    {
        delete m_pNanosuit;
        m_pNanosuit = nullptr;
    }
}