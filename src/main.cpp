#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct VertexData
{
    Vector3 Location{};
    Vector3 Color{};
};

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
                                     "out vec3 Position;"
                                     "out vec3 Color;"
                                     "layout (location = 0) in vec3 aPosition;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPosition, 1.0);\n"
                                     "   Position = aPosition;"
                                     "   Color = aColor;"
                                     "}\0";

    return CreateShader(vertexShaderSource, GL_VERTEX_SHADER, "VERTEX", vertexShader);
}

bool CreateFragmentShader1(unsigned int& fragmentShader2)
{
    const char* fragmentShader2Source = "#version 330 core\n"
                                        "in vec3 Position;"
                                        "in vec3 Color;"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = vec4(Color, 1.0f);\n"
                                        "}\0;";

    return CreateShader(fragmentShader2Source, GL_FRAGMENT_SHADER, "FRAGMENT", fragmentShader2);
}

bool CreateFragmentShader2(unsigned int& fragmentShader1)
{
    const char* fragmentShader1Source = "#version 330 core\n"
                                        "in vec3 Position;"
                                        "uniform float BlueColor;"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = vec4(-Position.xy, BlueColor, 1.0f);\n"
                                        "}\0;";

    return CreateShader(fragmentShader1Source, GL_FRAGMENT_SHADER, "FRAGMENT", fragmentShader1);
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

    unsigned int fragmentShader1;
    if (!CreateFragmentShader1(fragmentShader1))
        return -1;

    unsigned int fragmentShader2;
    if (!CreateFragmentShader2(fragmentShader2))
        return -1;

    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();

    if (!LinkShadersToProgram(shaderProgram1, vertexShader, fragmentShader1))
        return -1;

    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();

    if (!LinkShadersToProgram(shaderProgram2, vertexShader, fragmentShader2))
        return -1;

    std::vector<VertexData> Vertices1 = {
        // location          colour
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // top right
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // bottom right
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // top left
    };

    std::vector<Vector3> Vertices2 = {
        {0.5f, -0.5f, 0.0f},  // bottom right
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {-0.5f, 0.5f, 0.0f},  // top left
    };

    unsigned int VAOs[2];
    unsigned int VBOs[2];
    {
        glGenVertexArrays(2, VAOs);
        glGenBuffers(2, VBOs);

        {
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
            glBufferData(GL_ARRAY_BUFFER, Vertices1.size() * sizeof(VertexData), Vertices1.data(), GL_STATIC_DRAW);

            glBindVertexArray(VAOs[0]);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)sizeof(Vector3));
            glEnableVertexAttribArray(1);
        }

        {
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
            glBufferData(GL_ARRAY_BUFFER, Vertices2.size() * sizeof(Vector3), Vertices2.data(), GL_STATIC_DRAW);

            glBindVertexArray(VAOs[1]);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
            glEnableVertexAttribArray(0);
        }
    }

    glClearColor(0.f, 0.f, 0.0f, 1.0f);

    while (!ShouldCloseWindow(window))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        // update the uniform color
        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram2, "BlueColor");
        glUniform1f(vertexColorLocation, blueValue);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
