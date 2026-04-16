#include "GLRenderer.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/time_utils.h>
#include <iostream>

GLRenderer::GLRenderer() : m_pLightingShader(nullptr), m_pLightCubeShader(nullptr), m_cubeVAO(0), m_lightCubeVAO(0), m_VBO(0), m_diffuseMap(0), m_specularMap(0),
    camera(glm::vec3(0.0f, 0.0f, 3.0f)), lastX(800.0f / 2.0f), lastY(600.0f / 2.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f)
{
    m_cubePositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
    m_cubePositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
    m_cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
    m_cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
    m_cubePositions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
    m_cubePositions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
    m_cubePositions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
    m_cubePositions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
    m_cubePositions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
    m_cubePositions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);

    m_pointLightPositions[0] = glm::vec3( 0.7f,  0.2f,  2.0f);
    m_pointLightPositions[1] = glm::vec3( 2.3f, -3.3f, -4.0f);
    m_pointLightPositions[2] = glm::vec3(-4.0f,  2.0f, -12.0f);
    m_pointLightPositions[3] = glm::vec3( 0.0f,  0.0f, -3.0f);
}

void GLRenderer::OnInit()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    m_pLightingShader = new Shader("6.multiple_lights.vs", "6.multiple_lights.fs");
    m_pLightCubeShader = new Shader("6.light_cube.vs", "6.light_cube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &m_lightCubeVAO);
    glBindVertexArray(m_lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures
    m_diffuseMap = loadTexture(FileSystem::getPath("resources/textures/container2.png").c_str());
    m_specularMap = loadTexture(FileSystem::getPath("resources/textures/container2_specular.png").c_str());

    // shader configuration
    m_pLightingShader->use();
    m_pLightingShader->setInt("material.diffuse", 0);
    m_pLightingShader->setInt("material.specular", 1);
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

    // be sure to activate shader when setting uniforms/drawing objects
    if(m_pLightingShader)
    {
        m_pLightingShader->use();
        m_pLightingShader->setVec3("viewPos", camera.Position);
        m_pLightingShader->setFloat("material.shininess", 32.0f);

        // directional light
        m_pLightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_pLightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_pLightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_pLightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        m_pLightingShader->setVec3("pointLights[0].position", m_pointLightPositions[0]);
        m_pLightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        m_pLightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        m_pLightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setFloat("pointLights[0].constant", 1.0f);
        m_pLightingShader->setFloat("pointLights[0].linear", 0.09f);
        m_pLightingShader->setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        m_pLightingShader->setVec3("pointLights[1].position", m_pointLightPositions[1]);
        m_pLightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        m_pLightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        m_pLightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setFloat("pointLights[1].constant", 1.0f);
        m_pLightingShader->setFloat("pointLights[1].linear", 0.09f);
        m_pLightingShader->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        m_pLightingShader->setVec3("pointLights[2].position", m_pointLightPositions[2]);
        m_pLightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        m_pLightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        m_pLightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setFloat("pointLights[2].constant", 1.0f);
        m_pLightingShader->setFloat("pointLights[2].linear", 0.09f);
        m_pLightingShader->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        m_pLightingShader->setVec3("pointLights[3].position", m_pointLightPositions[3]);
        m_pLightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        m_pLightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        m_pLightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setFloat("pointLights[3].constant", 1.0f);
        m_pLightingShader->setFloat("pointLights[3].linear", 0.09f);
        m_pLightingShader->setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        m_pLightingShader->setVec3("spotLight.position", camera.Position);
        m_pLightingShader->setVec3("spotLight.direction", camera.Front);
        m_pLightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        m_pLightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        m_pLightingShader->setFloat("spotLight.constant", 1.0f);
        m_pLightingShader->setFloat("spotLight.linear", 0.09f);
        m_pLightingShader->setFloat("spotLight.quadratic", 0.032f);
        m_pLightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        m_pLightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        m_pLightingShader->setMat4("projection", projection);
        m_pLightingShader->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        m_pLightingShader->setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_specularMap);

        // render containers
        glBindVertexArray(m_cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_pLightingShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

         // also draw the lamp object(s)
         if(m_pLightCubeShader)
         {
             m_pLightCubeShader->use();
             m_pLightCubeShader->setMat4("projection", projection);
             m_pLightCubeShader->setMat4("view", view);

             // we now draw as many light bulbs as we have point lights.
             glBindVertexArray(m_lightCubeVAO);
             for (unsigned int i = 0; i < 4; i++)
             {
                 model = glm::mat4(1.0f);
                 model = glm::translate(model, m_pointLightPositions[i]);
                 model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
                 m_pLightCubeShader->setMat4("model", model);
                 glDrawArrays(GL_TRIANGLES, 0, 36);
             }
         }
    }
}

void GLRenderer::OnDestroy()
{
    glDeleteVertexArrays(1, &m_cubeVAO);
    glDeleteVertexArrays(1, &m_lightCubeVAO);
    glDeleteBuffers(1, &m_VBO);
    if (m_pLightingShader)
    {
        delete m_pLightingShader;
        m_pLightingShader = nullptr;
    }
    if (m_pLightCubeShader)
    {
        delete m_pLightCubeShader;
        m_pLightCubeShader = nullptr;
    }
}

unsigned int GLRenderer::loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}