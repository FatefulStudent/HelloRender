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

    void Tick(float deltaTime);
    bool ShouldCloseWindow() const;
    GLFWwindow* GetWindow() const { return m_window; }

    static float GetWidthPx();
    static float GetHeightPx();
    static float GetAspectRatio();

    static float GetLeftBorder();
    static float GetRightBorder();
    static float GetUpBorder();
    static float GetBottomBorder();

private:
    GLFWwindow* m_window = nullptr;
    GLFWwindow* CreateWindow() const;

    void Finalize();

    static float WidthPx;
    static float HeightPx;

    static float TargetHalfHeight;

    static void framebuffer_size_callback(GLFWwindow* window,
                                          int width,
                                          int height);
    static void error_callback(int error, const char* description);
};

#endif
