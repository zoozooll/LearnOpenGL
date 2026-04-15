#ifndef GLRENDERER_H
#define GLRENDERER_H

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
    unsigned int m_shaderProgram;
    unsigned int m_VAO;
    unsigned int m_VBO;
};

#endif //GLRENDERER_H