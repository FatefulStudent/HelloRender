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

ShaderProgram* CreateShaderProgramWithColorInVertexData() {
    const char* vertexPath =
        "src/Lessons/Shaders/shaders/shaderWithPositionAndColor.vert";
    const char* fragmentPath =
        "src/Lessons/Shaders/shaders/shaderThatUsesInColor.frag";

    return new ShaderProgram(vertexPath, fragmentPath);
}

ShaderProgram* CreateShaderProgramWithUniformColor() {
    const char* vertexPath =
        "src/Lessons/Shaders/shaders/shaderWithPositionAndColor.vert";
    const char* fragmentPath =
        "src/Lessons/Shaders/shaders/shaderWithUniformBlueColor.frag";

    return new ShaderProgram(vertexPath, fragmentPath);
}

}  // namespace Ex_2ShaderProgramsLocal

void Ex_2ShaderPrograms::Initialize() {
    BaseExcercise::Initialize();

    m_shaderProgramWithColorInVertex = Ex_2ShaderProgramsLocal::
        CreateShaderProgramWithColorInVertexData();
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
                     m_vertices1.size() * sizeof(VertexData),
                     m_vertices1.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAOs[0]);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                              (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                              (void*)sizeof(Vector3));
        glEnableVertexAttribArray(1);
    }

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, m_vertices2.size() * sizeof(Vector3),
                     m_vertices2.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAOs[1]);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3),
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

void Ex_2ShaderPrograms::Finalize() {
    BaseExcercise::Finalize();

    delete m_shaderProgramWithColorInVertex;
    delete m_shaderProgramWithUniformColor;
}
