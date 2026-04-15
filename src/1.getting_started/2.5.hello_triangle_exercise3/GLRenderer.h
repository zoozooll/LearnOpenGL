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
    unsigned int m_shaderProgramOrange;
    unsigned int m_shaderProgramYellow;
    unsigned int m_VAOs[2];
    unsigned int m_VBOs[2];
};

#endif //GLRENDERER_H