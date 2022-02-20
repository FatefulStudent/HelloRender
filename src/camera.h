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

    float m_fov = 45.0f;
    static Camera* m_camera;

    glm::mat4 m_view = {};
    glm::vec3 m_cameraPos = glm::vec3(0.f);
    glm::vec3 m_cameraUp = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraFront = {0.0f, 0.0f, -1.0f};
    glm::vec2 m_cachedCursorPos = glm::vec2(0.f);
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_cameraSpeed = 5.f;
    GLFWwindow* m_window;

public:
    Camera(GLFWwindow* window);
    ~Camera();

    void SetPosition(const glm::vec3& Position) { m_cameraPos = Position; };

    float GetFov() const { return m_fov; };
    glm::vec3 GetPosition() const { return m_cameraPos; };
    const glm::mat4& GetViewMatrix() const { return m_view; };

    void Tick(float deltaTime);
};

#endif