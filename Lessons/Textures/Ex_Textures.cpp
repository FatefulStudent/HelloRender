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

namespace TexturesLocal {

ShaderProgram* CreateShaderProgram() {
    const char* vertexShaderPath =
        "Lessons/Textures/shaders/shaderWithTexture.vert";
    const char* fragmentShaderPath =
        "Lessons/Textures/shaders/shaderWithTexture.frag";

    return new ShaderProgram(vertexShaderPath, fragmentShaderPath);
}
unsigned int CreateTexture() {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    const char* texturePath = "Resources/woodenContainer.jpg";
    unsigned char* data =
        stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture at path \"" << texturePath
                  << "\"" << std::endl;
        throw -1;
    }
    stbi_image_free(data);
    return texture;
}
}  // namespace TexturesLocal

void Ex_Textures::Initialize() {
    BaseExcercise::Initialize();

    m_texture = TexturesLocal::CreateTexture();

    m_vertices = {
        // positions          // colors           // texture coords
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},    // UR
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // DR
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // DL
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   // UL
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
        glBufferData(
            GL_ARRAY_BUFFER,
            m_vertices.size() * sizeof(VertexData_PosColorTexture),
            m_vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture),
                              (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture),
                              (void*)sizeof(Vector3));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(VertexData_PosColorTexture),
                              (void*)(2 * sizeof(Vector3)));
        glEnableVertexAttribArray(2);
    }

    m_shaderProgram = TexturesLocal::CreateShaderProgram();
}

void Ex_Textures::Tick() {
    BaseExcercise::Tick();

    m_shaderProgram->use();
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Ex_Textures::Finalize() {
    BaseExcercise::Finalize();
    delete m_shaderProgram;
}