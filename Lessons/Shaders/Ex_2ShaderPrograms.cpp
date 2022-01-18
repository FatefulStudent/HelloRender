#include "Ex_2ShaderPrograms.h"

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

namespace Ex_2ShaderProgramsLocal {

std::shared_ptr<ShaderProgram> CreateShaderProgramWithColorInVertexData() {
    const char* vertexPath =
        "Lessons/Shaders/shaders/shaderWithPositionAndColor.vert";
    const char* fragmentPath =
        "Lessons/Shaders/shaders/shaderThatUsesInColor.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<ShaderProgram> CreateShaderProgramWithUniformColor() {
    const char* vertexPath =
        "Lessons/Shaders/shaders/shaderWithPositionAndColor.vert";
    const char* fragmentPath =
        "Lessons/Shaders/shaders/shaderWithUniformBlueColor.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

}  // namespace Ex_2ShaderProgramsLocal

void Ex_2ShaderPrograms::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    m_shaderProgramWithColorInVertex =
        Ex_2ShaderProgramsLocal::CreateShaderProgramWithColorInVertexData();
    assert(m_shaderProgramWithColorInVertex);

    m_shaderProgramWithUniformColor =
        Ex_2ShaderProgramsLocal::CreateShaderProgramWithUniformColor();
    assert(m_shaderProgramWithUniformColor);

    m_vertices1 = {
        // location          colour
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},   // top right
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // bottom right
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},  // top left
    };

    m_vertices2 = {
        {0.5f, -0.5f, 0.0f},   // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.5f, 0.5f, 0.0f},   // top left
    };

    glGenVertexArrays(2, m_VAOs);
    glGenBuffers(2, m_VBOs);

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER,
                     m_vertices1.size() * sizeof(VertexData_PosColor),
                     m_vertices1.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAOs[0]);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColor), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColor),
                              (void*)sizeof(Vector3<float>));
        glEnableVertexAttribArray(1);
    }

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER,
                     m_vertices2.size() * sizeof(Vector3<float>),
                     m_vertices2.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAOs[1]);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3<float>),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }
}

void Ex_2ShaderPrograms::Tick() {
    BaseExcercise::Tick();

    {
        m_shaderProgramWithColorInVertex->use();
        glBindVertexArray(m_VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    {
        m_shaderProgramWithUniformColor->use();
        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        m_shaderProgramWithUniformColor->setFloat("BlueColor", blueValue);
        glBindVertexArray(m_VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
