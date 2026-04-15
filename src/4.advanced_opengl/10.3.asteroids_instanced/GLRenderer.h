#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <glm/glm.hpp>
#include <vector>

class Shader; // Forward declaration

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

private:
    Shader* m_pAsteroidShader;
    Shader* m_pPlanetShader;
    Model* m_pRockModel;
    Model* m_pPlanetModel;
    unsigned int m_instanceBuffer;
    unsigned int m_amount;
};

#endif //GLRENDERER_H