#include "Application.h"

#include <GL/glew.h>

#include <iostream>


float Application::WidthPx = 1280.0f;
float Application::HeightPx = 720.0f;

float Application::TargetHalfHeight = 20.0f;


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

void Application::Tick(float deltaTime) {
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

    window = glfwCreateWindow(WidthPx, HeightPx,
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
    return WidthPx;
}

float Application::GetHeightPx() {
    return HeightPx;
}

float Application::GetAspectRatio() {
    return WidthPx / HeightPx;
}

float Application::GetLeftBorder() {
    return -TargetHalfHeight * Application::GetAspectRatio();
}

float Application::GetRightBorder() {
    return TargetHalfHeight * Application::GetAspectRatio();    
}

float Application::GetUpBorder() {
    return TargetHalfHeight;
}

float Application::GetBottomBorder() {
    return -TargetHalfHeight;
}

void Application::framebuffer_size_callback(GLFWwindow* window,
                                            int width,
                                            int height) {
    //glViewport(0, 0, width, height);
}

void Application::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
