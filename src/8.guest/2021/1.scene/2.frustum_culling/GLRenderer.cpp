#include "GLRenderer.h"
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>
#include <learnopengl/time_utils.h>
#include <iostream>

GLRenderer::GLRenderer() :
    camera(glm::vec3(0.0f, 10.0f, 0.0f)), cameraSpy(glm::vec3(0.0f, 10.0f, 0.f)),
    lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    ourShader(nullptr), ourEntity(nullptr),
    m_width(800), m_height(600)
{
    camera.MovementSpeed = 20.f;
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
	Model model(FileSystem::getPath("resources/objects/planet/planet.obj"));
	ourEntity = new Entity(model);
	ourEntity->transform.setLocalPosition({ 0, 0, 0 });
	const float scale = 1.0;
	ourEntity->transform.setLocalScale({ scale, scale, scale });

	{
		Entity* lastEntity = ourEntity;

		for (unsigned int x = 0; x < 20; ++x)
		{
			for (unsigned int z = 0; z < 20; ++z)
			{
				ourEntity->addChild(model);
				lastEntity = ourEntity->children.back().get();

				//Set transform values
				lastEntity->transform.setLocalPosition({ x * 10.f - 100.f,  0.f, z * 10.f - 100.f });
			}
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
    float currentFrame = static_cast<float>(TimeUtils::GetTime());
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
        const Frustum camFrustum = createFrustumFromCamera(camera, (float)m_width / (float)m_height, glm::radians(camera.Zoom), 0.1f, 100.0f);

        cameraSpy.ProcessMouseMovement(2, 0);
        glm::mat4 view = camera.GetViewMatrix();

        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // draw our scene graph
        unsigned int total = 0, display = 0;
        ourEntity->drawSelfAndChild(camFrustum, *ourShader, display, total);
        std::cout << "Total process in CPU : " << total << " / Total send to GPU : " << display << std::endl;

        ourEntity->updateSelfAndChild();
    }
}

void GLRenderer::OnDestroy()
{
    if (ourShader) delete ourShader;
    if (ourEntity) delete ourEntity;
}
