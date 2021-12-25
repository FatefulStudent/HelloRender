#include "Test_2ShaderPrograms.h"

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

namespace Test_2ShaderProgramsLocal {

ShaderProgram* CreateShaderProgram1() {
    // @TODO: move to separate shader files
    const char* vertexShaderSource =
        "#version 420 core\n"
        "out vec3 Position;"
        "out vec3 Color;"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPosition, 1.0);\n"
        "   Position = aPosition;"
        "   Color = aColor;"
        "}\0";

    const char* fragmentShaderSource =
        "#version 420 core\n"
        "in vec3 Position;"
        "in vec3 Color;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(Color, 1.0f);\n"
        "}\0;";

    return new ShaderProgram(vertexShaderSource, fragmentShaderSource);
}

ShaderProgram* CreateShaderProgram2() {
    const char* vertexShaderSource =
        "#version 420 core\n"
        "out vec3 Position;"
        "out vec3 Color;"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPosition, 1.0);\n"
        "   Position = aPosition;"
        "   Color = aColor;"
        "}\0";

    const char* fragmentShaderSource =
        "#version 420 core\n"
        "in vec3 Position;"
        "uniform float BlueColor;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(-Position.xy, BlueColor, 1.0f);\n"
        "}\0;";

    return new ShaderProgram(vertexShaderSource, fragmentShaderSource);
}

}  // namespace Test_2ShaderProgramsLocal

void Test_2ShaderPrograms::Initialize() {
    BaseTest::Initialize();

    m_shaderProgram1 = Test_2ShaderProgramsLocal::CreateShaderProgram1();
    assert(m_shaderProgram1);

    m_shaderProgram2 = Test_2ShaderProgramsLocal::CreateShaderProgram2();
    assert(m_shaderProgram2);

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

void Test_2ShaderPrograms::Tick() {
    BaseTest::Tick();

    {
        m_shaderProgram1->use();
        glBindVertexArray(m_VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    {
        m_shaderProgram2->use();
        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        m_shaderProgram2->setFloat("BlueColor", blueValue);
        glBindVertexArray(m_VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

void Test_2ShaderPrograms::Finalize() {
    BaseTest::Finalize();

    delete m_shaderProgram1;
    delete m_shaderProgram2;
}
