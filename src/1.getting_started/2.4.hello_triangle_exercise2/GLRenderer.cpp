#include "GLRenderer.h"
#include <iostream>

GLRenderer::GLRenderer() : vertexShader(0), fragmentShader(0), shaderProgram(0) {
    VBOs[0] = 0;
    VBOs[1] = 0;
    VAOs[0] = 0;
    VAOs[1] = 0;
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
    glUseProgram(shaderProgram);
    
    // 绘制第一个三角形
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // 绘制第二个三角形
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLRenderer::cleanup() {
    // 清理OpenGL资源
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
    }
    if (fragmentShader) {
        glDeleteShader(fragmentShader);
    }
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (VAOs[0]) {
        glDeleteVertexArrays(2, VAOs);
    }
    if (VBOs[0]) {
        glDeleteBuffers(2, VBOs);
    }
}

void GLRenderer::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void GLRenderer::setupShaders() {
    // 顶点着色器源码
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    
    // 片段着色器源码
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    
    // 编译顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // 检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // 编译片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // 检查编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // 链接着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // 检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // 链接后删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GLRenderer::setupBuffers() {
    // 第一个三角形的顶点数据
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // 左下角
        -0.0f, -0.5f, 0.0f,  // 右下角
        -0.45f, 0.5f, 0.0f   // 顶部
    };
    
    // 第二个三角形的顶点数据
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,   // 左下角
        0.9f, -0.5f, 0.0f,   // 右下角
        0.45f, 0.5f, 0.0f    // 顶部
    };
    
    // 创建VAOs和VBOs
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    // 设置第一个三角形
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 设置第二个三角形
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VAO
    glBindVertexArray(0);
}