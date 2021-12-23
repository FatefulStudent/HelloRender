#ifndef APPLICATION_HELPER_H
#define APPLICATION_HELPER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace ApplicationHelper {
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
                              "Hello Render!", NULL, NULL);
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

GLFWwindow* StartApplication()
{
    GLFWwindow* window = ApplicationHelper::CreateWindow();

    if (!window)
        throw -1;

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW." << std::endl;
        FinalizeApplication();
        throw -1;
    }
}

void FinalizeApplication()
{
    glfwTerminate();
}

}  // namespace ApplicationHelper

#endif