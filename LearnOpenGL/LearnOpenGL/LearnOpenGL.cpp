// LearnOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

int main()
{
    std::cout << "Hello Learn OpenGL!\n";
    instantiateGLFWWindow();
    int windowStatus = createGLFWWindow(800, 600, "OpenGL Window");
    if (windowStatus == -1)
    {
        return -1;
    }
    int gladStatus = loadGLAD();
    if (gladStatus == -1)
    {
        return -1;
    }

}
