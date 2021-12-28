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
    const char* vertexPath = "Lessons/Textures/shaders/shaderWithTexture.vert";
    const char* fragmentPath =
        "Lessons/Textures/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

unsigned int CreateTexture(const char* texturePath) {
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
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum inputImageType = 0;
        if (nrChannels == 4)
            inputImageType = GL_RGBA;
        else if (nrChannels == 3)
            inputImageType = GL_RGB;
        else
            throw -1;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     inputImageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture at path \"" << texturePath << "\""
                  << std::endl;
        throw -1;
    }
    stbi_image_free(data);
    return texture;
}

void Ex_Textures::Initialize() {
    BaseExcercise::Initialize();

    m_texture1 = CreateTexture("Resources/woodContainer.jpg");
    m_texture2 = CreateTexture("Resources/awesomeFace.png");

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
    m_shaderProgram->setInt("Texture2", 1);
}

void Ex_Textures::Tick() {
    BaseExcercise::Tick();

    m_shaderProgram->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
