#include "Ex_Camera.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "mesh.h"
#include "shaderInstance.h"
#include "shaderProgram.h"
#include "texture.h"

#include <GL/glew.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/6. Camera/shaders/shaderWithModelViewProj.vert";
    const std::string fragmentPath =
        "Lessons/6. Camera/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Mesh> CreateMesh() {
    std::vector<VertexData_PosTexture> vertices = {
        // position             // texture coords
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},

        {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},

        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},

        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}};

    return std::make_shared<Mesh>(std::move(vertices));
}
}  // namespace

float Ex_Camera::fov = 45.0f;

void Ex_Camera::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    m_texture1 =
        std::make_shared<Texture>("Resources/woodContainer.jpg", GL_TEXTURE0);
    m_texture2 =
        std::make_shared<Texture>("Resources/awesomeFace.png", GL_TEXTURE1);

    m_mesh = CreateMesh();

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgram->use();
    m_shaderProgram->setInt("Texture1", 0);
    m_shaderProgram->setInt("Texture2", 1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetScrollCallback(window, ScrollCallback);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
    double cursorPosX, cursorPosY;
    glfwGetCursorPos(m_window, &cursorPosX, &cursorPosY);
    m_cachedCursorPos = {cursorPosX, cursorPosY};

    m_yaw = -90.0f;
    m_pitch = 0.f;
}

void Ex_Camera::ProcessInput(float deltaTime) {
    BaseExcercise::ProcessInput(deltaTime);

    // process camera movement
    {
        constexpr float cameraSpeed = 5.f;
        const float cameraDistance = deltaTime * cameraSpeed;

        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
            m_cameraPos += cameraDistance * m_cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
            m_cameraPos -= cameraDistance * m_cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
            m_cameraPos -=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) *
                cameraDistance;
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
            m_cameraPos +=
                glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) *
                cameraDistance;
        if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
            m_cameraPos += cameraDistance * m_cameraUp;
        if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
            m_cameraPos -= cameraDistance * m_cameraUp;
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
        m_pitch = std::min(89.0f, std::max(m_pitch, -89.0f));

        m_cachedCursorPos = {cursorPosX, cursorPosY};
    }
}

void Ex_Camera::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_cameraFront = glm::normalize(direction);

    glm::vec3 cameraTarget = m_cameraPos + direction;

    glm::mat4 view;
    view = glm::lookAt(m_cameraPos, cameraTarget, m_cameraUp);

    std::vector<glm::vec3> cubePositions = {
        {0.0f, 0.0f, 0.0f},     {2.0f, 5.0f, -15.0f}, {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f}, {2.4f, -0.4f, -3.5f}, {-1.7f, 3.0f, -7.5f},
        {1.3f, -2.0f, -2.5f},   {1.5f, 2.0f, -2.5f},  {1.5f, 0.2f, -1.5f},
        {-1.3f, 1.0f, -1.5f},
    };

    for (auto&& cubePosition : cubePositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePosition);

        const bool bHasPositivexAxis = cubePosition.x > 0;

        model =
            glm::rotate(model, glm::radians(50.0f) * glm::length(cubePosition),
                        glm::vec3(1.0f, 1.f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection =
            glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

        m_shaderProgram->use();
        m_shaderProgram->setMatrix("Model", model);
        m_shaderProgram->setMatrix("View", view);
        m_shaderProgram->setMatrix("Projection", projection);

        m_texture1->Bind();
        m_texture2->Bind();

        m_mesh->Draw();
    }
}

void Ex_Camera::ScrollCallback(GLFWwindow* window,
                               double xoffset,
                               double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 100.0f)
        fov = 100.0f;
}
