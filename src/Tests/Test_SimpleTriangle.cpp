#include "Test_SimpleTriangle.h"

#include "Helper/ApplicationHelper.h"
#include "Helper/VertexData.h"
#include "Helper/ShaderHelper.h"
#include "shaderInstance.h"
#include "shaderProgram.h"

#include <GL/glew.h>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

void Test_SimpleTriangle::Initialize() {
    BaseTest::Initialize();

    ShaderProgram* shaderProgram2 = ShaderHelper::CreateShaderProgram2();

    std::vector<Vector3> Vertices = {
        {0.5f, -0.5f, 0.0f},   // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.5f, 0.5f, 0.0f},   // top left
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER,
                        Vertices.size() * sizeof(Vector3),
                        Vertices.data(), GL_STATIC_DRAW);

        glBindVertexArray(m_VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                sizeof(Vector3), (void*)0);
        glEnableVertexAttribArray(0);
    }
    
}

void Test_SimpleTriangle::Tick() {
    BaseTest::Tick();
    
    m_shaderProgram->use();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Test_SimpleTriangle::Finalize() {
    BaseTest::Finalize();
    delete m_shaderProgram;
}