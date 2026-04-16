#include "GLRenderer.h"
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_t.h>
#include <learnopengl/time_utils.h>
#include <iostream>
#include <vector>

const unsigned int NUM_PATCH_PTS = 4;

GLRenderer::GLRenderer() :
    camera(glm::vec3(67.0f, 627.5f, 169.9f), glm::vec3(0.0f, 1.0f, 0.0f), -128.1f, -42.4f),
    lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    tessHeightMapShader(nullptr), terrainVAO(0), terrainVBO(0), texture(0), rez(20),
    m_width(800), m_height(600)
{
}

GLRenderer::~GLRenderer()
{
}

void GLRenderer::OnInit()
{
    GLint maxTessLevel;
    glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
    std::cout << "Max available tess level: " << maxTessLevel << std::endl;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    tessHeightMapShader = new Shader("8.3.gpuheight.vs","8.3.gpuheight.fs", nullptr, "8.3.gpuheight.tcs", "8.3.gpuheight.tes");

    // load and create a texture
    // -------------------------
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("heightmaps/iceland_heightmap.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        tessHeightMapShader->use();
        tessHeightMapShader->setInt("heightMap", 0);
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices;
    for(unsigned i = 0; i <= rez-1; i++)
    {
        for(unsigned j = 0; j <= rez-1; j++)
        {
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
        }
    }

    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);
    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    float currentFrame = static_cast<float>(TimeUtils::GetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (tessHeightMapShader) {
        tessHeightMapShader->use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        tessHeightMapShader->setMat4("projection", projection);
        tessHeightMapShader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        tessHeightMapShader->setMat4("model", model);

        glBindVertexArray(terrainVAO);
        glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * rez * rez);
    }
}

void GLRenderer::OnDestroy()
{
    if (tessHeightMapShader) delete tessHeightMapShader;
    glDeleteVertexArrays(1, &terrainVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteTextures(1, &texture);
}
