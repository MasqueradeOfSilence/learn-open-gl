/*
    Learn Open GL: Going through the tutorial to refresh my knowledge.
*/
#include <iostream>
// The glad header must go before glfw to avoid errors
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <string>
using namespace std;

void instantiateGLFWWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int createGLFWWindow(int width, int height, string title)
{
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        cout << "Error! Failed to create GLFW window!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
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

int main()
{
    std::cout << "Hello Learn OpenGL!\n";
    int width = 800;
    int height = 600;
    instantiateGLFWWindow();
    int windowStatus = createGLFWWindow(width, height, "OpenGL Window");
    if (windowStatus == -1)
    {
        return -1;
    }
    int gladStatus = loadGLAD();
    if (gladStatus == -1)
    {
        return -1;
    }
    setDimensionsOfRenderingWindow(width, height);

}
