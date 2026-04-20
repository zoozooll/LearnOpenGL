#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <vector>
#include <string>

class Shader;

struct VertexAL {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

struct AreaLight {
    glm::vec3 offset;
    float yRotation;
    glm::vec3 color;
    float intensity = 4.0f;
    bool twoSided = true;
};

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer() = default;

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

    bool keys[1024];

    void incrementRoughness(float step);

private:
    Shader* shaderLTC;
    Shader* shaderLightPlane;

    GLuint planeVBO, planeVAO;
    GLuint areaLightVBO, areaLightVAO;
    GLuint mat1, mat2;
    unsigned int concreteTexture;

    static const int NUM_AREA_LIGHTS = 16;
    AreaLight areaLights[NUM_AREA_LIGHTS];

    GLuint timeQuery;
    GLuint64 totalQueryTimeNs;
    GLuint64 numQueries;

    int m_width;
    int m_height;

    void configurePlane();
    void configureAreaLights();
    void renderPlane();
    void renderAreaLight();
    GLuint loadMTexture();
    GLuint loadLUTTexture();
    unsigned int loadTexture(const char* path, bool gammaCorrection);
};

#endif //GLRENDERER_H
