/*
    Learn Open GL: Going through the tutorial to refresh my knowledge.
*/
#include <iostream>
// The glad header must go before glfw to avoid errors
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
using namespace std;

struct Window
{
    GLFWwindow* window;
    int status;
};

void instantiateGLFWWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window createGLFWWindow(int width, int height, string title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        cout << "Error! Failed to create GLFW window!" << endl;
        glfwTerminate();
        Window errorWindow = { NULL, -1 };
        return errorWindow;
    }
    glfwMakeContextCurrent(window);
    Window successWindow = { window, 0 };
    return successWindow;
}

int loadGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Error! Failed to initialize GLAD!" << endl;
        return - 1;
    }
    return 0;
}

void setDimensionsOfRenderingWindow(int width, int height)
{
    glViewport(0, 0, width, height);
}

/*
*   Adjusts the viewport when we resize the OpenGL window. 
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setUpAutomaticViewportAdjustment(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void renderBlueGreenWindow()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void executeRenderCommands()
{
    renderBlueGreenWindow();
}

void processInput(GLFWwindow* window)
{
    // If ESC is hit, close the window.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void runRenderLoop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        executeRenderCommands();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int closeWindow()
{
    glfwTerminate();
    return 0;
}

int main()
{
    cout << "Hello Learn OpenGL!\n";
    int width = 800;
    int height = 600;
    instantiateGLFWWindow();
    Window window = createGLFWWindow(width, height, "OpenGL Window");
    if (window.status == -1)
    {
        return -1;
    }
    int gladStatus = loadGLAD();
    if (gladStatus == -1)
    {
        return -1;
    }
    setDimensionsOfRenderingWindow(width, height);
    setUpAutomaticViewportAdjustment(window.window);
    runRenderLoop(window.window);
    closeWindow();
}
