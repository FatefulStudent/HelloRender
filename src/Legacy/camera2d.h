#ifndef Camera2d_H
#define Camera2d_H

#include <glm/glm.hpp>

class GLFWwindow;

class Camera2d {
private:
    float m_fov = 45.0f;

    glm::mat4 m_view = {};
    glm::vec3 m_cameraPos = {0.0f, 0.0f, 40.0f};
    glm::vec3 m_cameraUp = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraFront = {0.0f, 0.0f, -1.0f};
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
public:
    Camera2d();
    ~Camera2d();

    float GetFov() const { return m_fov; };
    glm::vec3 GetPosition() const { return m_cameraPos; };
    const glm::mat4& GetViewMatrix() const { return m_view; };

    void Tick(float deltaTime);
};

#endif