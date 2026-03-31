#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <vector>

extern int width, height;

class GLRenderer {
private:
    // Shaders
    Shader* pbrShader;
    Shader* equirectangularToCubemapShader;
    Shader* irradianceShader;
    Shader* backgroundShader;
    
    // Camera
    Camera* camera;
    
    // Vertex Array Objects
    unsigned int sphereVAO;
    unsigned int cubeVAO;
    unsigned int indexCount;
    
    // Framebuffer objects
    unsigned int captureFBO;
    unsigned int captureRBO;
    
    // Textures
    unsigned int hdrTexture;
    unsigned int envCubemap;
    unsigned int irradianceMap;
    
    // Timing
    float deltaTime, lastFrame;
    
    // Lights
    glm::vec3 lightPositions[4];
    glm::vec3 lightColors[4];
    int nrRows, nrColumns;
    float spacing;
    
    // Helper functions
    void renderSphere();
    void renderCube();
    
public:
    GLRenderer();
    ~GLRenderer();
    
    void initialize();
    void render();
    void cleanup();
    
    // Window resize
    void onSizeChanged(int width, int height);
    
    // Getters
    Camera* getCamera();
    float getDeltaTime();
    float getLastFrame();
    
    // Setters
    void setLastFrame(float frame);
};

#endif // GLRENDERER_H