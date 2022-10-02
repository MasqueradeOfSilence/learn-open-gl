// LearnOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
// The glad header must go before glfw to avoid errors
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

void instantiateGLFWWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main()
{
    std::cout << "Hello Learn OpenGL!\n";
    instantiateGLFWWindow();
}
