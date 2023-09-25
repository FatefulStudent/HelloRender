#include "Application.h"

#include <GL/glew.h>

#include <iostream>


float Application::widthPx = 1280.0f;
float Application::heightPx = 720.0f;

float Application::targetHalfHeight = 20.0f;


Application::Application() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        throw -1;
    }

    Window = CreateWindow();

    if (!Window) {
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

void Application::Tick(double deltaTime) {
    glfwSwapBuffers(Window);
    glfwPollEvents();
}

void Application::Finalize() {
    glfwTerminate();
}

GLFWwindow* Application::CreateWindow() const {
    GLFWwindow* window = nullptr;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(widthPx, heightPx,
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
    return glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
           glfwWindowShouldClose(Window) == 1;
}

float Application::GetWidthPx() {
    return widthPx;
}

float Application::GetHeightPx() {
    return heightPx;
}

float Application::GetAspectRatio() {
    return widthPx / heightPx;
}

float Application::GetLeftBorder() {
    return -targetHalfHeight * Application::GetAspectRatio();
}

float Application::GetRightBorder() {
    return targetHalfHeight * Application::GetAspectRatio();    
}

float Application::GetUpBorder() {
    return targetHalfHeight;
}

float Application::GetBottomBorder() {
    return -targetHalfHeight;
}

void Application::framebuffer_size_callback(GLFWwindow* window,
                                            int width,
                                            int height) {
    //glViewport(0, 0, width, height);
}

void Application::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
