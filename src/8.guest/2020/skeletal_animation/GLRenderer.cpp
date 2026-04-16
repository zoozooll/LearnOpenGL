#include "GLRenderer.h"
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/time_utils.h>
#include <iostream>

GLRenderer::GLRenderer() :
    camera(glm::vec3(0.0f, 0.0f, 3.0f)), lastX(400.0f), lastY(300.0f), firstMouse(true),
    deltaTime(0.0f), lastFrame(0.0f),
    ourShader(nullptr), ourModel(nullptr), danceAnimation(nullptr), animator(nullptr),
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
	ourShader = new Shader("anim_model.vs", "anim_model.fs");

	// load models
	// -----------
	ourModel = new Model(FileSystem::getPath("resources/objects/vampire/dancing_vampire.dae"));
	danceAnimation = new Animation(FileSystem::getPath("resources/objects/vampire/dancing_vampire.dae"), ourModel);
	animator = new Animator(danceAnimation);
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

    if (animator)
        animator->UpdateAnimation(deltaTime);

    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ourShader && ourModel && animator)
    {
        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)m_width / (float)m_height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        auto transforms = animator->GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            ourShader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
        ourShader->setMat4("model", model);
        ourModel->Draw(*ourShader);
    }
}

void GLRenderer::OnDestroy()
{
    if (ourShader) delete ourShader;
    if (ourModel) delete ourModel;
    if (danceAnimation) delete danceAnimation;
    if (animator) delete animator;
}
