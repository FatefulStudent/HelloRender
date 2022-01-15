#include "Ex_Additionals.h"

#include "Helper/ApplicationHelper.h"
#include "Helper/VertexData.h"
#include "shaderInstance.h"
#include "shaderProgram.h"

#include <GL/glew.h>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace AdditionalsLocal {

std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const char* vertexPath =
        "Lessons/Shaders/shaders/inverted_OutPos_UniformOffset.vert";
    const char* fragmentPath =
        "Lessons/Shaders/shaders/colorBasedOnPosition.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}
}  // namespace AdditionalsLocal

void Ex_Additionals::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    m_shaderProgram = AdditionalsLocal::CreateShaderProgram();

    m_vertices = {
        {0.5f, -0.5f, 0.0f},   // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.0f, 0.5f, 0.0f},   // top left
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3f),
                     m_vertices.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }
}

void Ex_Additionals::Tick() {
    BaseExcercise::Tick();

    float timeValue = glfwGetTime();
    float XOffset = (sin(timeValue) / 2.0f);
    m_shaderProgram->setFloat("XOffset", XOffset);
    m_shaderProgram->use();

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
