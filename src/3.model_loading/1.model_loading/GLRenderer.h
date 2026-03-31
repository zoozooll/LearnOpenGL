#ifndef GL_RENDERER_H
#define GL_RENDERER_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

extern int width, height;

class Model;

class GLRenderer {
public:
    GLRenderer();
    virtual ~GLRenderer();

    void initialize();
    void render();
    void cleanup();
    void onSizeChanged(int width, int height);
    
    // Camera accessor
    Camera* getCamera();

private:
    // Shaders
    Shader* ourShader;

    // Model
    Model* ourModel;

    // Camera
    Camera* camera;

    void setupShaders();
    void loadModel();
};

#endif // GL_RENDERER_H