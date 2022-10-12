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

// Triangle vertex shader
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 apos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

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
*   Adjusts the viewport when we resize the OpenGL window, so the rendered image is resized.
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

/*
* Vertex buffer objects are an efficient way of sending large amounts of vertices to the GPU.
*/
unsigned int createVertexBufferObject(float triangleVertices[])
{
    // Defining our buffer
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    // Giving the buffer a type (array for the triangle vertices)
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    // Actually inserting the vertices into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    return vertexBufferObject;
}

void checkForCompileTimeErrors(unsigned int vertexShader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Error: Building vertex shader failed!\n" << infoLog << endl;
    }
}

unsigned int buildVertexShader()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader code to the shader object and compile it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkForCompileTimeErrors(vertexShader);
    return vertexShader;
}

void renderTriangle()
{
    // Defining a 2D triangle with z-coordinates of 0.
    float triangleVertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    unsigned int vertexBufferObject = createVertexBufferObject(triangleVertices);
    unsigned int vertexShader = buildVertexShader();
}

void executeRenderCommands()
{
    renderBlueGreenWindow();
    renderTriangle();
}

void processInputFromPeripherals(GLFWwindow* window)
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
        processInputFromPeripherals(window);
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
    return closeWindow();
}
