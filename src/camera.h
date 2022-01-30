#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class GLFWwindow;

class Camera {
private:
    static void ScrollCallback(GLFWwindow* window,
                               double xoffset,
                               double yoffset);
    void SetupInput();

    static float m_fov;

    glm::mat4 m_view = {};
    glm::vec3 m_cameraPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_cameraUp = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraFront = {0.0f, 0.0f, -1.0f};
    glm::vec2 m_cachedCursorPos = {0.0f, 0.0f};
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    GLFWwindow* m_window;

public:
    Camera(GLFWwindow* window);
    ~Camera();

    static float GetFov() { return m_fov; };
    const glm::mat4& GetViewMatrix() const { return m_view; };

    void Tick(float deltaTime);
};

#endif