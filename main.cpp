// GameOfLife.cpp : Defines the entry point for the application.

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

static void Print(const char* text, const char* file, int line)
{
    printf("%s\t%s at line %i\n", text, file, line);
}

static void PrintLog(const char* text, const char* file, int line, const char* logText)
{
    printf("%s\t%s at line %i\nLog:\n%s\n", text, file, line, logText);
}

#define Print(text) Print(text, __FILE__, __LINE__);
#define PrintLog(text, logText) PrintLog(text, __FILE__, __LINE__, logText)

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
"}\0";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

int main()
{
#pragma region Initialization
    GLFWwindow* m_window;

    /*Initialize the library*/
    if (!glfwInit())
    {
        Print("[INIT] GLFW dit not initiate correctly.");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    m_window = glfwCreateWindow(1920, 1080, "Game Of Life", NULL, NULL);

    if (!m_window)
    {
        Print("[INIT] Setup failed! m_window = nullptr");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Print("[INIT] Setup failed! glad did not load correctly.");
        glfwTerminate();
        return -1;
    }

    printf("[INIT] Setup passed. Entering run loop.");
#pragma endregion

#pragma region VBO
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    /* Vertex Buffer Object Creation */
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#pragma endregion

#pragma region Shader Creation
    /* Vertex Shader Creation */
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    /* Fragment Shader Creation */
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    /* Compilation and error check */
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        PrintLog("[SHADER] Vertex Shader creation failed.", infoLog);
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        PrintLog("[SHADER] Fragment Shader creation failed.", infoLog);
    }

    /* Shader program creation */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        PrintLog("[SHADER] Shader Program creation failed.", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#pragma endregion

    while (!glfwWindowShouldClose(m_window))
    {
        /*render here*/
        glClear(GL_COLOR_BUFFER_BIT);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Copy vertices array over to buffer for OpenGL
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 1. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // 2. use our shader program when we want to render an object
        glUseProgram(shaderProgram);
        // 3. now draw the object 

        /*swap front and back buffers*/
        glfwSwapBuffers(m_window);

        /*Poll and process events*/
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
