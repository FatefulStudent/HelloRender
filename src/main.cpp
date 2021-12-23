#include "shaderInstance.h"
#include "shaderProgram.h"
#include "Helper/ShaderHelper.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

struct Vector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct VertexData {
    Vector3 Location{};
    Vector3 Color{};
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* CreateWindow() {
    GLFWwindow* window = nullptr;
    const int InitialWindowWidth = 800;
    const int InitialWindowHeight = 600;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(InitialWindowWidth, InitialWindowHeight,
                              "Hello World!", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to init GLFW window." << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

bool ShouldCloseWindow(GLFWwindow* window) {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(window) == 1;
}

int main(void) {
    GLFWwindow* window = CreateWindow();

    if (!window)
        return -1;

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW." << std::endl;
        glfwTerminate();
        return -1;
    }

    ShaderProgram* shaderProgram1 = ShaderHelper::CreateShaderProgram1();
    ShaderProgram* shaderProgram2 = ShaderHelper::CreateShaderProgram2();

    std::vector<VertexData> Vertices1 = {
        // location          colour
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},   // top right
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // bottom right
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},  // top left
    };

    std::vector<Vector3> Vertices2 = {
        {0.5f, -0.5f, 0.0f},   // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.5f, 0.5f, 0.0f},   // top left
    };

    unsigned int VAOs[2];
    unsigned int VBOs[2];
    {
        glGenVertexArrays(2, VAOs);
        glGenBuffers(2, VBOs);

        {
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
            glBufferData(GL_ARRAY_BUFFER,
                         Vertices1.size() * sizeof(VertexData),
                         Vertices1.data(), GL_STATIC_DRAW);

            glBindVertexArray(VAOs[0]);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(VertexData), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(VertexData),
                                  (void*)sizeof(Vector3));
            glEnableVertexAttribArray(1);
        }

        {
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
            glBufferData(GL_ARRAY_BUFFER,
                         Vertices2.size() * sizeof(Vector3),
                         Vertices2.data(), GL_STATIC_DRAW);

            glBindVertexArray(VAOs[1]);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(Vector3), (void*)0);
            glEnableVertexAttribArray(0);
        }
    }

    glClearColor(0.f, 0.f, 0.0f, 1.0f);

    while (!ShouldCloseWindow(window)) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClear(GL_COLOR_BUFFER_BIT);

        {
            shaderProgram1->use();
            glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        {
            shaderProgram2->use();
            float timeValue = glfwGetTime();
            float blueValue = sin(timeValue) / 2.0f + 0.5f;
            shaderProgram2->setFloat("BlueColor", blueValue);
            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete shaderProgram1;
    delete shaderProgram2;

    glfwTerminate();
    return 0;
}
