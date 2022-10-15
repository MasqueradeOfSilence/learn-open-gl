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
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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

void checkForCompileTimeErrorsFragment(unsigned int fragmentShader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "Error: Building fragment shader failed!\n" << infoLog << endl;
    }
}

void checkForCompileTimeErrorsVertex(unsigned int vertexShader)
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
    checkForCompileTimeErrorsVertex(vertexShader);
    return vertexShader;
}

// Calculates the color output of the pixels. 
unsigned int buildFragmentShader()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkForCompileTimeErrorsFragment(fragmentShader);
    return fragmentShader;
}

void checkForShaderLinkingErrors(unsigned int shaderProgram)
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "Error: Linking shaders failed!\n" << infoLog << endl;
    }
}

// Links all the shaders together
unsigned int buildShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkForShaderLinkingErrors(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void renderTriangle(unsigned int vertexBufferObject, unsigned int vertexArrayObject, unsigned int shaderProgram = NULL)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void executeRenderCommands(unsigned int vertexBufferObject = NULL, unsigned int vertexArrayObject = NULL, unsigned int shaderProgram = NULL)
{
    renderBlueGreenWindow();
    renderTriangle(vertexBufferObject, vertexArrayObject, shaderProgram);
}

void processInputFromPeripherals(GLFWwindow* window)
{
    // If ESC is hit, close the window.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// not ideal to pass the VBO/VAO for clean code but we don't need to run it every loop
void runRenderLoop(GLFWwindow* window, unsigned int vertexBufferObject = NULL, unsigned int vertexArrayObject = NULL, unsigned int shaderProgram = NULL)
{
    while (!glfwWindowShouldClose(window))
    {
        processInputFromPeripherals(window);
        executeRenderCommands(vertexBufferObject, vertexArrayObject, shaderProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int closeWindow()
{
    glfwTerminate();
    return 0;
}

/*
*  A good rule for following this tutorial is to NOT abstract out things to functions until your code is compiling.
*/
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
    unsigned int vertexShader = buildVertexShader();
    unsigned int fragmentShader = buildFragmentShader();
    unsigned int shaderProgram = buildShaderProgram(vertexShader, fragmentShader);
    // We don't need the original shaders after linking them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    float triangleVertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    // Vertex buffer objects are an efficient way of sending large amounts of vertices to the GPU.
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    // 3 vertices stored sequentially, tightly packed
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    runRenderLoop(window.window, VBO, VAO, shaderProgram);
    return closeWindow();
}
