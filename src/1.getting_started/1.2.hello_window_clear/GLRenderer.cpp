#include "GLRenderer.h"
#include <learnopengl/gl_header.h>

void GLRenderer::OnInit()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::OnDestroy()
{
}