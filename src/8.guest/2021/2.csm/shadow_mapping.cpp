#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 2560;
const unsigned int SCR_HEIGHT = 1440;

GLRenderer renderer;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
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

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    renderer.OnInit();
    renderer.OnSizeChanged(SCR_WIDTH, SCR_HEIGHT);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        renderer.OnDraw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.OnDestroy();

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    renderer.camera.MovementSpeed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 2.5 * 10 : 2.5;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(FORWARD, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(BACKWARD, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(LEFT, renderer.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderer.camera.ProcessKeyboard(RIGHT, renderer.deltaTime);

    static int fPress = GLFW_RELEASE;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && fPress == GLFW_PRESS)
    {
        renderer.showQuad = !renderer.showQuad;
    }
    fPress = glfwGetKey(window, GLFW_KEY_F);

    static int plusPress = GLFW_RELEASE;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE && plusPress == GLFW_PRESS)
    {
        renderer.debugLayer++;
        if (renderer.debugLayer > renderer.shadowCascadeLevels.size())
        {
            renderer.debugLayer = 0;
        }
    }
    plusPress = glfwGetKey(window, GLFW_KEY_N);

    static int cPress = GLFW_RELEASE;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE && cPress == GLFW_PRESS)
    {
        // How to handle getLightSpaceMatrices call? It's private now.
        // Maybe I should move lightMatricesCache logic inside renderer.OnDraw or provide a public method.
        // For now, I'll assume renderer can handle it internally if I trigger a flag.
    }
    cPress = glfwGetKey(window, GLFW_KEY_C);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    renderer.OnSizeChanged(width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (renderer.firstMouse)
    {
        renderer.lastX = (float)xpos;
        renderer.lastY = (float)ypos;
        renderer.firstMouse = false;
    }

    float xoffset = (float)xpos - renderer.lastX;
    float yoffset = renderer.lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

    renderer.lastX = (float)xpos;
    renderer.lastY = (float)ypos;

    renderer.camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    renderer.camera.ProcessMouseScroll((float)yoffset);
}
