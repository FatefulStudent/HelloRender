#include "Ex_Textures.h"

#include "Helper/ApplicationHelper.h"
#include "Helper/VertexData.h"
#include "shaderInstance.h"
#include "shaderProgram.h"

#include <GL/glew.h>
#include "stb_image.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/Textures/shaders/shaderWithTexture.vert";
    const std::string fragmentPath =
        "Lessons/Textures/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

void Ex_Textures::Initialize() {
    BaseExcercise::Initialize();

    m_texture1 =
        std::make_shared<Texture>("Resources/woodContainer.jpg", GL_TEXTURE0);
    m_texture2 =
        std::make_shared<Texture>("Resources/awesomeFace.png", GL_TEXTURE1);

    m_vertices = {
        // positions          // colors           // texture coords
        {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},    // UR
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // DR
        {{-0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // DL
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   // UL
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    {
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     m_vertices.size() * sizeof(VertexData_PosColorTexture),
                     m_vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture),
                              (void*)sizeof(Vector2));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture),
                              (void*)(sizeof(Vector2) + sizeof(Vector3)));
        glEnableVertexAttribArray(2);
    }

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgram->use();
    m_shaderProgram->setInt("Texture1", 0);
    m_shaderProgram->setInt("Texture2", 1);
}

void Ex_Textures::Tick() {
    BaseExcercise::Tick();

    m_shaderProgram->use();
    m_texture1->Bind();
    m_texture2->Bind();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
