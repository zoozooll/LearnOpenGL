#include "GLRenderer.h"
#include <iostream>

GLRenderer::GLRenderer() {
    VBOs[0] = 0;
    VBOs[1] = 0;
    VAOs[0] = 0;
    VAOs[1] = 0;
    vertexShader = 0;
    fragmentShaderOrange = 0;
    fragmentShaderYellow = 0;
    shaderProgramOrange = 0;
    shaderProgramYellow = 0;
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
    
    // 使用橙色着色器程序
    glUseProgram(shaderProgramOrange);
    // 绑定第一个VAO并绘制第一个三角形
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // 使用黄色着色器程序
    glUseProgram(shaderProgramYellow);
    // 绑定第二个VAO并绘制第二个三角形
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLRenderer::cleanup() {
    // 清理OpenGL资源
    if (shaderProgramOrange) {
        glDeleteProgram(shaderProgramOrange);
    }
    if (shaderProgramYellow) {
        glDeleteProgram(shaderProgramYellow);
    }
    if (fragmentShaderOrange) {
        glDeleteShader(fragmentShaderOrange);
    }
    if (fragmentShaderYellow) {
        glDeleteShader(fragmentShaderYellow);
    }
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (VAOs[0] || VAOs[1]) {
        glDeleteVertexArrays(2, VAOs);
    }
    if (VBOs[0] || VBOs[1]) {
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
    
    // 橙色片段着色器源码
    const char* fragmentShader1Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    
    // 黄色片段着色器源码
    const char* fragmentShader2Source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    
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
    
    // 编译橙色片段着色器
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    
    // 检查编译错误
    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::ORANGE::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // 编译黄色片段着色器
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    
    // 检查编译错误
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::YELLOW::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // 链接橙色着色器程序
    shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    
    // 检查链接错误
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::ORANGE::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // 链接黄色着色器程序
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    
    // 检查链接错误
    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::YELLOW::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void GLRenderer::setupBuffers() {
    // 第一个三角形的顶点数据
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // 左
        -0.0f, -0.5f, 0.0f,  // 右
        -0.45f, 0.5f, 0.0f,  // 上
    };
    
    // 第二个三角形的顶点数据
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // 左
        0.9f, -0.5f, 0.0f,  // 右
        0.45f, 0.5f, 0.0f   // 上
    };
    
    // 创建两个VAO和两个VBO
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    // 第一个三角形的设置
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 第二个三角形的设置
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    // 解绑VAO
    glBindVertexArray(0);
}