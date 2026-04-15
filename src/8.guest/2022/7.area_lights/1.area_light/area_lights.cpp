#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement(GLfloat deltaTime);

GLRenderer renderer;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL: Area Lights", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    renderer.OnInit();
    renderer.OnSizeChanged(800, 600);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		do_movement(renderer.deltaTime);
        renderer.OnDraw();
        glfwSwapBuffers(window);
    }

    renderer.OnDestroy();
    glfwTerminate();
    return 0;
}

void do_movement(GLfloat deltaTime)
{
	float cameraSpeed = deltaTime * 3.0f;
    if(renderer.keys[GLFW_KEY_W]) renderer.camera.ProcessKeyboard(FORWARD, cameraSpeed);
    else if(renderer.keys[GLFW_KEY_S]) renderer.camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    if(renderer.keys[GLFW_KEY_A]) renderer.camera.ProcessKeyboard(LEFT, cameraSpeed);
    else if(renderer.keys[GLFW_KEY_D]) renderer.camera.ProcessKeyboard(RIGHT, cameraSpeed);

    if (renderer.keys[GLFW_KEY_R]) {
	    if (renderer.keys[GLFW_KEY_LEFT_SHIFT]) renderer.incrementRoughness(0.01f);
	    else renderer.incrementRoughness(-0.01f);
    }
    if (renderer.keys[GLFW_KEY_I]) {
	    if (renderer.keys[GLFW_KEY_LEFT_SHIFT]) renderer.incrementLightIntensity(0.025f);
	    else renderer.incrementLightIntensity(-0.025f);
    }
    if (renderer.keys[GLFW_KEY_LEFT]) renderer.areaLightTranslate.z += 0.01f;
    if (renderer.keys[GLFW_KEY_RIGHT]) renderer.areaLightTranslate.z -= 0.01f;
    if (renderer.keys[GLFW_KEY_UP]) renderer.areaLightTranslate.y += 0.01f;
    if (renderer.keys[GLFW_KEY_DOWN]) renderer.areaLightTranslate.y -= 0.01f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    static unsigned short wireframe = 0;
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); return;
        case GLFW_KEY_B: renderer.switchTwoSided(true); break;
        default: if (key >= 0 && key < 1024) renderer.keys[key] = true; break;
        }
    }
    if(action == GLFW_RELEASE)
    {
        if(key == GLFW_KEY_SPACE) {
            if(wireframe == 0) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe = 1; }
            else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); wireframe = 0; }
        }
        else { if (key >= 0 && key < 1024) renderer.keys[key] = false; }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { renderer.OnSizeChanged(width, height); }

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (renderer.firstMouse) { renderer.lastX = xpos; renderer.lastY = ypos; renderer.firstMouse = false; }
    float xoffset = xpos - renderer.lastX;
    float yoffset = renderer.lastY - ypos;
    renderer.lastX = xpos; renderer.lastY = ypos;
    renderer.camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { renderer.camera.ProcessMouseScroll(static_cast<float>(yoffset)); }
