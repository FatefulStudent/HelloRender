#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/glm.hpp>

class GLFWwindow;

class Camera3d {
private:
    static void ScrollCallback(GLFWwindow* window,
                               double xoffset,
                               double yoffset);
    void SetupInput();

    float m_fov = 45.0f;
    static Camera3d* m_camera;

    glm::mat4 m_view = {};
    glm::vec3 m_cameraPos = {0.0f, 0.0f, 10.0f};
    glm::vec3 m_cameraUp = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraFront = {0.0f, 0.0f, -1.0f};
    glm::vec2 m_cachedCursorPos = {0.0f, 0.0f};
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_cameraSpeed = 5.f;
    GLFWwindow* Window;

public:
    Camera3d(GLFWwindow* window);
    ~Camera3d();

    float GetFov() const { return m_fov; };
    glm::vec3 GetPosition() const { return m_cameraPos; };
    const glm::mat4& GetViewMatrix() const { return m_view; };

    void Tick(float deltaTime);
};

#endif