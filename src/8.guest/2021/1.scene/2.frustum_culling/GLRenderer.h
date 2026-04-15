#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <learnopengl/entity.h>

class Shader;

class GLRenderer
{
public:
    GLRenderer();
    virtual ~GLRenderer();

    virtual void OnInit();
    virtual void OnSizeChanged(int width, int height);
    virtual void OnDraw();
    virtual void OnDestroy();

    // Camera
    Camera camera;
    Camera cameraSpy;
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

private:
    Shader* ourShader;
    Entity* ourEntity;

    int m_width;
    int m_height;
};

#endif //GLRENDERER_H
