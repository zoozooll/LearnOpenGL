#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <glm/glm.hpp>

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

private:
    Shader* m_pShader;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_texture1;
    unsigned int m_texture2;
    glm::vec3* m_pCubePositions;
};

#endif //GLRENDERER_H