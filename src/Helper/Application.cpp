#include "Application.h"

#include <GL/glew.h>

#include <iostream>

Application::Application() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        throw -1;
    }

    m_window = CreateWindow();

    if (!m_window) {
        Finalize();
        throw -1;
    }

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW." << std::endl;
        Finalize();
        throw -1;
    }
}

Application::~Application() {
    Finalize();
}

void Application::Tick(float deltaTime) {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Application::Finalize() {
    glfwTerminate();
}

GLFWwindow* Application::CreateWindow() const {
    GLFWwindow* window = nullptr;
    const int InitialWindowWidth = 1080;
    const int InitialWindowHeight = 1080;

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

bool Application::ShouldCloseWindow() const {
    return glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(m_window) == 1;
}

void Application::framebuffer_size_callback(GLFWwindow* window,
                                            int width,
                                            int height) {
    glViewport(0, 0, width, height);
}

void Application::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
