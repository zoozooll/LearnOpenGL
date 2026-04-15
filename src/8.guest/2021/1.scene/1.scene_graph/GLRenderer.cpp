#include "GLRenderer.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>
#include <iostream>

GLRenderer::GLRenderer() :
    camera(glm::vec3(0.0f, 0.0f, 3.0f)), lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    ourShader(nullptr), ourEntity(nullptr),
    m_width(800), m_height(600)
{
}

GLRenderer::~GLRenderer()
{
}

void GLRenderer::OnInit()
{
	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	ourShader = new Shader("1.model_loading.vs", "1.model_loading.fs");

	// load entities
	// -----------
	Model model = Model(FileSystem::getPath("resources/objects/planet/planet.obj"));
	ourEntity = new Entity(model);
	ourEntity->transform.setLocalPosition({ 10, 0, 0 });
	const float scale = 0.75;
	ourEntity->transform.setLocalScale({ scale, scale, scale });

	{
		Entity* lastEntity = ourEntity;

		for (unsigned int i = 0; i < 10; ++i)
		{
			lastEntity->addChild(model);
			lastEntity = lastEntity->children.back().get();

			//Set transform values
			lastEntity->transform.setLocalPosition({ 10, 0, 0 });
			lastEntity->transform.setLocalScale({ scale, scale, scale });
		}
	}
	ourEntity->updateSelfAndChild();
}

void GLRenderer::OnSizeChanged(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void GLRenderer::OnDraw()
{
    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ourShader && ourEntity)
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // draw our scene graph
        Entity* lastEntity = ourEntity;
        while (lastEntity->children.size())
        {
            ourShader->setMat4("model", lastEntity->transform.getModelMatrix());
            lastEntity->pModel->Draw(*ourShader);
            lastEntity = lastEntity->children.back().get();
        }

        ourEntity->transform.setLocalRotation({ 0.f, ourEntity->transform.getLocalRotation().y + 20 * deltaTime, 0.f });
        ourEntity->updateSelfAndChild();
    }
}

void GLRenderer::OnDestroy()
{
    if (ourShader) delete ourShader;
    if (ourEntity) delete ourEntity; // This will recursively delete children due to unique_ptr
}
