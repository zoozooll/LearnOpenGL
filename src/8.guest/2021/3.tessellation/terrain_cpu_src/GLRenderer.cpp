#include "GLRenderer.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader_m.h>
#include <iostream>
#include <vector>

GLRenderer::GLRenderer() :
    camera(glm::vec3(67.0f, 627.5f, 169.9f), glm::vec3(0.0f, 1.0f, 0.0f), -128.1f, -42.4f),
    lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    useWireframe(0), displayGrayscale(0),
    heightMapShader(nullptr), terrainVAO(0), terrainVBO(0), terrainIBO(0),
    numStrips(0), numTrisPerStrip(0),
    m_width(800), m_height(600)
{
}

GLRenderer::~GLRenderer()
{
}

void GLRenderer::OnInit()
{
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    heightMapShader = new Shader("8.3.cpuheight.vs","8.3.cpuheight.fs");

    // load image
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("heightmaps/iceland_heightmap.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }

    // set up vertex data
    std::vector<float> vertices;
    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = nrChannels;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];
            vertices.push_back( -height/2.0f + height*i/(float)height );   // vx
            vertices.push_back( (int) y * yScale - yShift);   // vy
            vertices.push_back( -width/2.0f + width*j/(float)width );   // vz
        }
    }
    stbi_image_free(data);

    std::vector<unsigned> indices;
    for(unsigned i = 0; i < height-1; i += rez)
    {
        for(unsigned j = 0; j < width; j += rez)
        {
            for(unsigned k = 0; k < 2; k++)
            {
                indices.push_back(j + width * (i + k*rez));
            }
        }
    }

    numStrips = (height-1)/rez;
    numTrisPerStrip = (width/rez)*2-2;

    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &terrainIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (heightMapShader) {
        heightMapShader->use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        heightMapShader->setMat4("projection", projection);
        heightMapShader->setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        heightMapShader->setMat4("model", model);

        glBindVertexArray(terrainVAO);
        if (useWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for(unsigned strip = 0; strip < numStrips; strip++)
        {
            glDrawElements(GL_TRIANGLE_STRIP, numTrisPerStrip+2, GL_UNSIGNED_INT, (void*)(sizeof(unsigned) * (numTrisPerStrip+2) * strip));
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GLRenderer::OnDestroy()
{
    if (heightMapShader) delete heightMapShader;
    glDeleteVertexArrays(1, &terrainVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteBuffers(1, &terrainIBO);
}
