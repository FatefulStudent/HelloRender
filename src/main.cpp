#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

bool CreateShader(const char* shaderSource, int shaderType, const char* shaderTypeForLog, unsigned int& outShader)
{
    outShader = glCreateShader(shaderType);
    glShaderSource(outShader, 1, &shaderSource, NULL);
    glCompileShader(outShader);

    int success;
    glGetShaderiv(outShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        static char infoLog[512];
        glGetShaderInfoLog(outShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << *shaderTypeForLog << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}

bool CreateVertexShader(unsigned int& vertexShader)
{
    const char* vertexShaderSource = "#version 420 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    return CreateShader(vertexShaderSource, GL_VERTEX_SHADER, "VERTEX", vertexShader);
}

bool CreateFragmentShader(unsigned int& fragmentShader)
{
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0;";

    return CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER, "FRAGMENT", fragmentShader);
}

GLFWwindow* CreateWindow()
{
    GLFWwindow* window = nullptr;
    const int InitialWindowWidth = 800;
    const int InitialWindowHeight = 600;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(InitialWindowWidth, InitialWindowHeight, "Hello World!", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to init GLFW window." << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

bool LinkShadersToProgram(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        static char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool ShouldCloseWindow(GLFWwindow* window)
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) == 1;
}

int main(void)
{
    GLFWwindow* window = CreateWindow();

    if (!window)
        return -1;

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to init GLEW." << std::endl;
        glfwTerminate();
        return -1;
    }

    unsigned int vertexShader;
    if (!CreateVertexShader(vertexShader))
        return -1;

    unsigned int fragmentShader;
    if (!CreateFragmentShader(fragmentShader))
        return -1;

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    if (!LinkShadersToProgram(shaderProgram, vertexShader, fragmentShader))
        return -1;

    float vertices[] = {
        // first triangle
        0.5f, 0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f, // top left
        // second triangle
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    // unsigned int indices[] = {
    //     0, 1, 2, // first triangle
    //     1, 2, 3,
    //     0, 3, 4 // second triangle
    // };

    unsigned int VAO;
    {
        glGenVertexArrays(1, &VAO);

        // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
        // 1. bind Vertex Array Object ???????
        glBindVertexArray(VAO);
    }

    unsigned int VBO;
    {
        glGenBuffers(1, &VBO);

        // 0. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 1. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // unsigned int EBO;
    // {
    //     glGenBuffers(1, &EBO);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // }

    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);

    glClearColor(0.f, 0.f, 1.0f, 1.0f);

    while (!ShouldCloseWindow(window))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
