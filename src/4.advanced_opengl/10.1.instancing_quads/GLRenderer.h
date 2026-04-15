#ifndef GLRENDERER_H
#define GLRENDERER_H

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
    unsigned int m_quadVAO;
    unsigned int m_quadVBO;
    unsigned int m_instanceVBO;
};

#endif //GLRENDERER_H