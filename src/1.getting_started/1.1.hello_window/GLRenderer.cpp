#include "GLRenderer.h"

void GLRenderer::OnInit() {}

void GLRenderer::OnSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw() {}

void GLRenderer::OnDestroy() {}
