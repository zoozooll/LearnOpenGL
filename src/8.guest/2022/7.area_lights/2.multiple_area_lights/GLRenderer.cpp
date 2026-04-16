#include "GLRenderer.h"
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/time_utils.h>
#include "../ltc_matrix.hpp"
#include "../colors.hpp"
#include <iostream>
#include <functional>
#include <chrono>
#include <random>

const glm::vec3 LIGHT_COLOR = Color::BurlyWood;
const GLfloat psize = 10.0f;
VertexAL planeVertices[6] = {
    { {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
    { {-psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
    { { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
    { {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
    { { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
    { { psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} }
};
VertexAL areaLightVertices[6] = {
    { {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    { {-8.0f, 2.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
    { {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
    { {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
    { {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
    { {-8.0f, 0.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }
};

GLRenderer::GLRenderer() :
    camera(glm::vec3(-0.224556, 10.4038, -18.9259), glm::vec3(0.0f, 1.0f, 0.0f), 89.3999, -34.3001),
    lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    shaderLTC(nullptr), shaderLightPlane(nullptr),
    planeVBO(0), planeVAO(0), areaLightVBO(0), areaLightVAO(0),
    mat1(0), mat2(0), concreteTexture(0), timeQuery(0), totalQueryTimeNs(0), numQueries(0),
    m_width(800), m_height(600)
{
    for (int i = 0; i < 1024; ++i) keys[i] = false;
}

void GLRenderer::OnInit()
{
    glEnable(GL_DEPTH_TEST);
    mat1 = loadMTexture();
    mat2 = loadLUTTexture();
    shaderLTC = new Shader("7.multi_area_light.vs", "7.multi_area_light.fs");
    shaderLightPlane = new Shader("7.light_plane.vs", "7.light_plane.fs");
    concreteTexture = loadTexture(FileSystem::getPath("resources/textures/concreteTexture.png").c_str(), true);

    configurePlane();
    configureAreaLights();

    shaderLTC->use();
    for (int i = 0; i < NUM_AREA_LIGHTS; i++)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, areaLights[i].offset);
        model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 p0 = glm::vec3(model * glm::vec4(areaLightVertices[0].position, 1.0f));
        glm::vec3 p1 = glm::vec3(model * glm::vec4(areaLightVertices[1].position, 1.0f));
        glm::vec3 p2 = glm::vec3(model * glm::vec4(areaLightVertices[4].position, 1.0f));
        glm::vec3 p3 = glm::vec3(model * glm::vec4(areaLightVertices[5].position, 1.0f));
        std::string base = "areaLights[" + std::to_string(i) + "].";
        shaderLTC->setVec3(base + "points[0]", p0);
        shaderLTC->setVec3(base + "points[1]", p1);
        shaderLTC->setVec3(base + "points[2]", p2);
        shaderLTC->setVec3(base + "points[3]", p3);
        shaderLTC->setVec3(base + "color", areaLights[i].color);
        shaderLTC->setFloat(base + "intensity", 2.0f);
        shaderLTC->setInt(base + "twoSided", 1);
    }
    shaderLTC->setInt("numAreaLights", NUM_AREA_LIGHTS);
    shaderLTC->setInt("LTC1", 0);
    shaderLTC->setInt("LTC2", 1);
    shaderLTC->setInt("material.diffuse", 2);
    incrementRoughness(0.0f);

    shaderLightPlane->use();
    shaderLightPlane->setVec3("lightColor", LIGHT_COLOR);

    glGenQueries(1, &timeQuery);
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    m_width = width; m_height = height;
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    float currentFrame = static_cast<float>(TimeUtils::GetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderLTC->use();
    glm::mat4 model(1.0f);
    shaderLTC->setMat4("model", model);
    shaderLTC->setMat3("normalMatrix", glm::mat3(model));
    glm::mat4 view = camera.GetViewMatrix();
    shaderLTC->setMat4("view", view);
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
    shaderLTC->setMat4("projection", projection);
    shaderLTC->setVec3("viewPosition", camera.Position);

    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, mat1);
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, mat2);
    glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, concreteTexture);

    glBeginQuery(GL_TIME_ELAPSED, timeQuery);
    renderPlane();
    glEndQuery(GL_TIME_ELAPSED);

    shaderLightPlane->use();
    shaderLightPlane->setMat4("view", view);
    shaderLightPlane->setMat4("projection", projection);
    for (int i = 0; i < NUM_AREA_LIGHTS; i++)
    {
        model = glm::translate(glm::mat4(1.0f), areaLights[i].offset);
        model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        shaderLightPlane->setMat4("model", model);
        shaderLightPlane->setVec3("lightColor", areaLights[i].color);
        renderAreaLight();
    }

    GLuint64 elapsed = 0;
    glGetQueryObjectui64v(timeQuery, GL_QUERY_RESULT, &elapsed);
    numQueries++;
    totalQueryTimeNs += elapsed;
}

void GLRenderer::OnDestroy()
{
    double measuredAverageMs = ((double)totalQueryTimeNs / (double)numQueries) * 1.0e-6;
    std::cout << "Total average time(ms) = " << measuredAverageMs << '\n';

    if (shaderLTC) delete shaderLTC;
    if (shaderLightPlane) delete shaderLightPlane;
    glDeleteQueries(1, &timeQuery);
    glDeleteVertexArrays(1, &planeVAO); glDeleteBuffers(1, &planeVBO);
    glDeleteVertexArrays(1, &areaLightVAO); glDeleteBuffers(1, &areaLightVBO);
    glDeleteTextures(1, &mat1); glDeleteTextures(1, &mat2);
    glDeleteTextures(1, &concreteTexture);
}

void GLRenderer::configurePlane()
{
    glGenVertexArrays(1, &planeVAO); glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO); glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); glEnableVertexAttribArray(2);
}

void GLRenderer::configureAreaLights()
{
    std::uniform_real_distribution<GLfloat> random_floats(0.0f, 1.0f);
    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    auto fn = [&](){ return random_floats(generator); };
    for (int i = 0; i < NUM_AREA_LIGHTS; i++) {
        float x = fn(); x = (x > 0.5f) ? x : -x;
        float z = fn(); z = (z > 0.5f) ? z : -z;
        areaLights[i].offset = glm::vec3(x, 0.0f, z) * 8.f;
        areaLights[i].yRotation = fn() * glm::two_pi<float>();
        areaLights[i].color = glm::vec3(fn(), fn(), fn());
    }
    glGenVertexArrays(1, &areaLightVAO); glGenBuffers(1, &areaLightVBO);
    glBindVertexArray(areaLightVAO); glBindBuffer(GL_ARRAY_BUFFER, areaLightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(areaLightVertices), areaLightVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat))); glEnableVertexAttribArray(2);
}

void GLRenderer::renderPlane() { glBindVertexArray(planeVAO); glDrawArrays(GL_TRIANGLES, 0, 6); glBindVertexArray(0); }
void GLRenderer::renderAreaLight() { glBindVertexArray(areaLightVAO); glDrawArrays(GL_TRIANGLES, 0, 6); glBindVertexArray(0); }

GLuint GLRenderer::loadMTexture() {
    GLuint texture = 0; glGenTextures(1, &texture); glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0); return texture;
}

GLuint GLRenderer::loadLUTTexture() {
    GLuint texture = 0; glGenTextures(1, &texture); glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0); return texture;
}

void GLRenderer::incrementRoughness(float step) {
    static float roughness = 0.5f; roughness += step; roughness = glm::clamp(roughness, 0.0f, 1.0f);
    if (shaderLTC) { shaderLTC->use(); shaderLTC->setVec4("material.albedoRoughness", glm::vec4(Color::SlateGray, roughness)); }
}

unsigned int GLRenderer::loadTexture(const char* path, bool gammaCorrection) {
    unsigned int textureID; glGenTextures(1, &textureID);
    int width, height, nrComponents; unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum internalFormat, dataFormat;
        if (nrComponents == 1) internalFormat = dataFormat = GL_RED;
        else if (nrComponents == 3) { internalFormat = gammaCorrection ? GL_SRGB : GL_RGB; dataFormat = GL_RGB; }
        else if (nrComponents == 4) { internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA; dataFormat = GL_RGBA; }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    return textureID;
}
