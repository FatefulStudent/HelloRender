#include "Ex_SimpleTriangle.h"

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

namespace SimpleTriangleLocal {

ShaderProgram* CreateShaderProgram() {
    const char* vertexShaderPath =
        "Lessons/HelloTriangle/shaders/simpleShader.vert";
    const char* fragmentShaderPath =
        "Lessons/HelloTriangle/shaders/simpleShader.frag";

    return new ShaderProgram(vertexShaderPath, fragmentShaderPath);
}
}  // namespace SimpleTriangleLocal

void Ex_SimpleTriangle::Initialize() {
    BaseExcercise::Initialize();

    m_shaderProgram = SimpleTriangleLocal::CreateShaderProgram();

    m_vertices = {
        {0.5f, -0.5f, 0.0f},   // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.0f, 0.5f, 0.0f},   // top left
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3),
                     m_vertices.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3),
                              (void*)0);
        glEnableVertexAttribArray(0);
    }
}

void Ex_SimpleTriangle::Tick() {
    BaseExcercise::Tick();

    m_shaderProgram->use();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Ex_SimpleTriangle::Finalize() {
    BaseExcercise::Finalize();
    delete m_shaderProgram;
}