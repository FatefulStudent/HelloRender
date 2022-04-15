#include "camera2d.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>


Camera2d::Camera2d() {}

Camera2d::~Camera2d() {}

void Camera2d::Tick(float deltaTime) {

    // calculate view matrix
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        direction.y = sin(glm::radians(m_pitch));
        direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_cameraFront = glm::normalize(direction);

        glm::vec3 cameraTarget = m_cameraPos + direction;

        m_view = glm::lookAt(m_cameraPos, cameraTarget, m_cameraUp);
    }
}