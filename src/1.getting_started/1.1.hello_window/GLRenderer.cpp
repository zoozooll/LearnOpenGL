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
    // 渲染逻辑
}

void GLRenderer::cleanup() {
    // 清理OpenGL资源
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}