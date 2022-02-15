#include "camera.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

float Camera::m_fov = 45.0f;

void Camera::SetupInput() {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(m_window, ScrollCallback);

    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
    glfwSetCursorPos(m_window, windowWidth / 2, windowHeight / 2);
    double cursorPosX, cursorPosY;
    glfwGetCursorPos(m_window, &cursorPosX, &cursorPosY);
    m_cachedCursorPos = {cursorPosX, cursorPosY};
}

void Camera::ScrollCallback(GLFWwindow* window,
                            double xoffset,
                            double yoffset) {
    m_fov -= (float)yoffset;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 100.0f)
        m_fov = 100.0f;
}

Camera::Camera(GLFWwindow* window) {
    m_window = window;
    SetupInput();
}

Camera::~Camera() {}

void Camera::Tick(float deltaTime) {
    // process camera movement
    {
        constexpr float cameraSpeed = 5.f;
        const float cameraDistance = deltaTime * cameraSpeed;

        glm::vec3 moveDirection = {0.0f, 0.0f, 0.0f};

        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
            moveDirection += m_cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
            moveDirection -= m_cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
            moveDirection -=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
            moveDirection +=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp));

        if (moveDirection != glm::vec3(0.0f, 0.0f, 0.0f))
            moveDirection = glm::normalize(
                glm::vec3(moveDirection.x, 0.0f, moveDirection.z));

        m_cameraPos += moveDirection * cameraDistance;
    }

    // process camera rotation
    {
        double cursorPosX, cursorPosY;
        glfwGetCursorPos(m_window, &cursorPosX, &cursorPosY);

        float xOffset = cursorPosX - m_cachedCursorPos.x;
        float yOffset = m_cachedCursorPos.y - cursorPosY;

        float sensitivity = 0.1f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        m_yaw += xOffset;
        m_pitch += yOffset;
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);

        m_cachedCursorPos = {cursorPosX, cursorPosY};
    }

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