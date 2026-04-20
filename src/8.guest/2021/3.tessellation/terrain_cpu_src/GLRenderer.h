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

    int useWireframe;
    int displayGrayscale;

private:
    Shader* heightMapShader;
    unsigned int terrainVAO, terrainVBO, terrainIBO;
    unsigned int numStrips;
    unsigned int numTrisPerStrip;

    int m_width;
    int m_height;
};

#endif //GLRENDERER_H
