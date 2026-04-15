#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <vector>

class Shader;

struct VertexAL {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
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

    glm::vec3 areaLightTranslate;
    bool keys[1024];

    void incrementRoughness(float step);
    void incrementLightIntensity(float step);
    void switchTwoSided(bool doSwitch);

private:
    Shader* shaderLTC;
    Shader* shaderLightPlane;

    GLuint planeVBO, planeVAO;
    GLuint areaLightVBO, areaLightVAO;
    GLuint mat1, mat2;
    unsigned int concreteTexture;

    int m_width;
    int m_height;

    void configureMockupData();
    void renderPlane();
    void renderAreaLight();
    GLuint loadMTexture();
    GLuint loadLUTTexture();
    unsigned int loadTexture(const char *path, bool gammaCorrection);
};

#endif //GLRENDERER_H
