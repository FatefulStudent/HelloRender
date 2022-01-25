#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

class Application {
public:
    Application();
    ~Application();

    void Tick();
    bool ShouldCloseWindow() const;
    GLFWwindow* GetWindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
    GLFWwindow* CreateWindow() const;

    void Finalize();

    static void framebuffer_size_callback(GLFWwindow* window,
                                          int width,
                                          int height);
    static void error_callback(int error, const char* description);
};

#endif
