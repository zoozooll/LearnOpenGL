#include "GLRenderer.h"
#include <learnopengl/shader_m.h>
#include <learnopengl/shader_c.h>
#include <learnopengl/time_utils.h>
#include <iostream>

const unsigned int TEXTURE_WIDTH = 1000, TEXTURE_HEIGHT = 1000;

GLRenderer::GLRenderer() : m_screenQuadShader(nullptr), m_computeShader(nullptr), m_texture(0),
    m_quadVAO(0), m_quadVBO(0), m_width(800), m_height(600), m_fCounter(0), m_deltaTime(0.0f), m_lastFrame(0.0f)
{
}

void GLRenderer::OnInit()
{
    m_screenQuadShader = new Shader("screenQuad.vs", "screenQuad.fs");
    m_computeShader = new ComputeShader("computeShader.cs");

    m_screenQuadShader->use();
    m_screenQuadShader->setInt("tex", 0);

    glGenTextures(1, &m_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    float currentFrame = static_cast<float>(TimeUtils::GetTime());
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    if(m_fCounter > 500) {
        std::cout << "FPS: " << 1 / m_deltaTime << std::endl;
        m_fCounter = 0;
    } else {
        m_fCounter++;
    }

    m_computeShader->use();
    m_computeShader->setFloat("t", currentFrame);
    glDispatchCompute((unsigned int)TEXTURE_WIDTH/10, (unsigned int)TEXTURE_HEIGHT/10, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_screenQuadShader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    renderQuad();
}

void GLRenderer::OnDestroy()
{
    if (m_screenQuadShader) delete m_screenQuadShader;
    if (m_computeShader) delete m_computeShader;
    glDeleteTextures(1, &m_texture);
    glDeleteVertexArrays(1, &m_quadVAO);
    glDeleteBuffers(1, &m_quadVBO);
}

void GLRenderer::renderQuad()
{
	if (m_quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		glGenVertexArrays(1, &m_quadVAO);
		glGenBuffers(1, &m_quadVBO);
		glBindVertexArray(m_quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(m_quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
