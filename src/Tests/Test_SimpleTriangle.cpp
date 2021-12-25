#include "Test_SimpleTriangle.h"

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

// @TODO: move to separate shader files
ShaderInstance* CreateVertexShader() {
    const char* vertexShaderSource =
        "#version 420 core\n"
        "out vec3 Position;"
        "layout (location = 0) in vec3 aPosition;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPosition, 1.0);\n"
        "   Position = aPosition;"
        "}\0";

    return new ShaderInstance(EShaderType::Vertex, vertexShaderSource);
}

ShaderInstance* CreateFragmentShader() {
    const char* fragmentShaderSource =
        "#version 420 core\n"
        "in vec3 Position;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(Position, 0.0f);\n"
        "}\0;";

    return new ShaderInstance(EShaderType::Fragment, fragmentShaderSource);
}

ShaderProgram* CreateShaderProgram() {
    ShaderInstance* vertexShaderInstance = CreateVertexShader();
    ShaderInstance* fragmentShaderInstance1 = CreateFragmentShader();
    return new ShaderProgram(vertexShaderInstance,
                             fragmentShaderInstance1);
}
}  // namespace SimpleTriangleLocal

void Test_SimpleTriangle::Initialize() {
    BaseTest::Initialize();

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