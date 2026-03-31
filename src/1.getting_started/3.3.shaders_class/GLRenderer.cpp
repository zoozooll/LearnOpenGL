#include "GLRenderer.h"
#include <iostream>

GLRenderer::GLRenderer() : VBO(0), VAO(0), ourShader(nullptr) {
}

GLRenderer::~GLRenderer() {
    cleanup();
}

void GLRenderer::initialize() {
    setupShaders();
    setupBuffers();
}

void GLRenderer::render() {
    // 清空颜色缓冲区
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 使用着色器程序
    ourShader->use();
    
    // 绑定VAO并绘制
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLRenderer::cleanup() {
    // 清理OpenGL资源
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    if (ourShader) {
        delete ourShader;
        ourShader = nullptr;
    }
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void GLRenderer::setupShaders() {
    // 创建Shader对象
    ourShader = new Shader("3.3.shader.vs", "3.3.shader.fs");
}

void GLRenderer::setupBuffers() {
    // 顶点数据 - 包含位置和颜色
    float vertices[] = {
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下角
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下角
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };
    
    // 创建VAO和VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // 绑定VAO
    glBindVertexArray(VAO);
    
    // 绑定VBO并填充数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 配置位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 配置颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // 解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}