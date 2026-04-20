#include "GLRenderer.h"
#include <learnopengl/gl_header.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/time_utils.h>
#include <iostream>
#include <cmath>

GLRenderer::GLRenderer() : m_pShader(nullptr), m_pRockModel(nullptr), m_pPlanetModel(nullptr), m_pModelMatrices(nullptr), m_amount(1000),
    camera(glm::vec3(0.0f, 0.0f, 55.0f)), lastX(800.0f / 2.0f), lastY(600.0f / 2.0f), firstMouse(true),
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
    m_pShader = new Shader("10.2.instancing.vs", "10.2.instancing.fs");

    // load models
    // -----------
    m_pRockModel = new Model(FileSystem::getPath("resources/objects/rock/rock.obj"));
    m_pPlanetModel = new Model(FileSystem::getPath("resources/objects/planet/planet.obj"));

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    m_pModelMatrices = new glm::mat4[m_amount];
    srand(static_cast<unsigned int>(TimeUtils::GetTime())); // initialize random seed
    float radius = 50.0;
    float offset = 2.5f;
    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)m_amount * 360.0f;
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
        m_pModelMatrices[i] = model;
    }
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
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 1000.0f);
    glm::mat4 view = camera.GetViewMatrix();;
    if(m_pShader)
    {
        m_pShader->use();
        m_pShader->setMat4("projection", projection);
        m_pShader->setMat4("view", view);

        // draw planet
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        m_pShader->setMat4("model", model);
        if(m_pPlanetModel)
            m_pPlanetModel->Draw(*m_pShader);

        // draw meteorites
        if(m_pRockModel)
        {
            for (unsigned int i = 0; i < m_amount; i++)
            {
                m_pShader->setMat4("model", m_pModelMatrices[i]);
                m_pRockModel->Draw(*m_pShader);
            }
        }
    }
}

void GLRenderer::OnDestroy()
{
    if (m_pShader)
    {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pRockModel)
    {
        delete m_pRockModel;
        m_pRockModel = nullptr;
    }
    if (m_pPlanetModel)
    {
        delete m_pPlanetModel;
        m_pPlanetModel = nullptr;
    }
    if (m_pModelMatrices)
    {
        delete[] m_pModelMatrices;
        m_pModelMatrices = nullptr;
    }
}