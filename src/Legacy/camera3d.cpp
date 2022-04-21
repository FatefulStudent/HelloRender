#include "camera3d.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

Camera3d* Camera3d::m_camera = nullptr;

void Camera3d::SetupInput() {
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(Window, ScrollCallback);

    int windowWidth, windowHeight;
    glfwGetWindowSize(Window, &windowWidth, &windowHeight);
    glfwSetCursorPos(Window, windowWidth / 2, windowHeight / 2);
    double cursorPosX, cursorPosY;
    glfwGetCursorPos(Window, &cursorPosX, &cursorPosY);
    m_cachedCursorPos = {cursorPosX, cursorPosY};
}

void Camera3d::ScrollCallback(GLFWwindow* window,
                            double xoffset,
                            double yoffset) {
    if (!m_camera)
        return;
    auto& fov = m_camera->m_fov;
    fov -= (float)yoffset;
    fov = std::clamp(fov, 1.0f, 100.0f);
}

Camera3d::Camera3d(GLFWwindow* window) {
    m_camera = this;
    Window = window;
    SetupInput();
}

Camera3d::~Camera3d() {}

void Camera3d::Tick(float deltaTime) {
    // process camera movement
    {
        const float cameraDistance = deltaTime * m_cameraSpeed;

        glm::vec3 moveDirection = {0.0f, 0.0f, 0.0f};

        if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
            moveDirection += m_cameraFront;
        if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
            moveDirection -= m_cameraFront;
        if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
            moveDirection -=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
        if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
            moveDirection +=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
        if (glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS)
            m_cameraSpeed *= 1.05f;
        if (glfwGetKey(Window, GLFW_KEY_Q) == GLFW_PRESS)
            m_cameraSpeed /= 1.05f;

        // if (moveDirection != glm::vec3(0.0f, 0.0f, 0.0f))
        //     moveDirection = glm::normalize(
        //         glm::vec3(moveDirection.x, 0.0f, moveDirection.z));

        m_cameraPos += moveDirection * cameraDistance;
    }

    // process camera rotation
    {
        double cursorPosX, cursorPosY;
        glfwGetCursorPos(Window, &cursorPosX, &cursorPosY);

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