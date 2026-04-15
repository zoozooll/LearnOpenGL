#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    renderer.OnInit();
    renderer.OnSizeChanged(SCR_WIDTH, SCR_HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        renderer.OnDraw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.OnDestroy();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(FORWARD, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(BACKWARD, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(LEFT, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(RIGHT, renderer.deltaTime);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if (renderer.exposure > 0.0f)
            renderer.exposure -= 0.001f;
        else
            renderer.exposure = 0.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        renderer.exposure += 0.001f;
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	    renderer.programChoice = 1;
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	    renderer.programChoice = 2;
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	    renderer.programChoice = 3;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    renderer.OnSizeChanged(width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (renderer.firstMouse)
    {
        renderer.lastX = xpos;
        renderer.lastY = ypos;
        renderer.firstMouse = false;
    }
    float xoffset = xpos - renderer.lastX;
    float yoffset = renderer.lastY - ypos;
    renderer.lastX = xpos;
    renderer.lastY = ypos;
    renderer.camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    renderer.camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
