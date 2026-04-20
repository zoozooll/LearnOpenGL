#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <learnopengl/gl_header.h>
#include <glm/glm.hpp>
#include <learnopengl/camera.h>
#include <vector>

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
    float lastX;
    float lastY;
    bool firstMouse;

    // Timing
    float deltaTime;
    float lastFrame;

private:
    Shader* tessHeightMapShader;
    unsigned int terrainVAO, terrainVBO;
    unsigned int texture;
    unsigned int rez;

    int m_width;
    int m_height;
};

#endif //GLRENDERER_H
