#include "GLRenderer.h"

GLRenderer::GLRenderer() {
}

GLRenderer::~GLRenderer() {
    cleanup();
}

void GLRenderer::initialize() {
    // 初始化OpenGL相关状态
}

void GLRenderer::render() {
    // 渲染逻辑 - 清空颜色缓冲区
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLRenderer::cleanup() {
    // 清理OpenGL资源
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}