#include "GLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <iostream>

GLRenderer::GLRenderer() : m_pShaderRed(nullptr), m_pShaderGreen(nullptr), m_pShaderBlue(nullptr), m_pShaderYellow(nullptr),
    m_cubeVAO(0), m_cubeVBO(0), m_uboMatrices(0),
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
    m_pShaderRed = new Shader("8.advanced_glsl.vs", "8.red.fs");
    m_pShaderGreen = new Shader("8.advanced_glsl.vs", "8.green.fs");
    m_pShaderBlue = new Shader("8.advanced_glsl.vs", "8.blue.fs");
    m_pShaderYellow = new Shader("8.advanced_glsl.vs", "8.yellow.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
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
    // cube VAO
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_cubeVBO);
    glBindVertexArray(m_cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // configure a uniform buffer object
    // ---------------------------------
    // first. We get the relevant block indices
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(m_pShaderRed->ID, "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(m_pShaderGreen->ID, "Matrices");
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(m_pShaderBlue->ID, "Matrices");
    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(m_pShaderYellow->ID, "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(m_pShaderRed->ID, uniformBlockIndexRed, 0);
    glUniformBlockBinding(m_pShaderGreen->ID, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(m_pShaderBlue->ID, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(m_pShaderYellow->ID, uniformBlockIndexYellow, 0);
    // Now actually create the buffer
    glGenBuffers(1, &m_uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    glm::mat4 projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

    // set the view matrix in the uniform block - we only have to do this once per loop iteration.
    glm::mat4 view = camera.GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // draw 4 cubes
    // RED
    glBindVertexArray(m_cubeVAO);
    if(m_pShaderRed)
    {
        m_pShaderRed->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
        m_pShaderRed->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // GREEN
    if(m_pShaderGreen)
    {
        m_pShaderGreen->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
        m_pShaderGreen->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // YELLOW
    if(m_pShaderYellow)
    {
        m_pShaderYellow->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
        m_pShaderYellow->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // BLUE
    if(m_pShaderBlue)
    {
        m_pShaderBlue->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
        m_pShaderBlue->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void GLRenderer::OnDestroy()
{
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteBuffers(1, &m_cubeVBO);
    glDeleteBuffers(1, &m_uboMatrices);
    if (m_pShaderRed)
    {
        delete m_pShaderRed;
        m_pShaderRed = nullptr;
    }
    if (m_pShaderGreen)
    {
        delete m_pShaderGreen;
        m_pShaderGreen = nullptr;
    }
    if (m_pShaderBlue)
    {
        delete m_pShaderBlue;
        m_pShaderBlue = nullptr;
    }
    if (m_pShaderYellow)
    {
        delete m_pShaderYellow;
        m_pShaderYellow = nullptr;
    }
}