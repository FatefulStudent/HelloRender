#include "mesh.h"

#include <GL/glew.h>

Mesh::Mesh(std::vector<VertexData_PosTexture>&& vertexData,
           std::vector<unsigned>&& indexData) {
    m_indices = indexData;
    m_vertices = vertexData;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    if (m_indices.size() > 0) {
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     m_indices.size() * sizeof(unsigned), m_indices.data(),
                     GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(VertexData_PosTexture),
                 m_vertices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(
        VertexData_PosTexture::GetIndexForPosition(),
        VertexData_PosTexture::GetNumberOfComponentsForPosition(), GL_FLOAT,
        GL_FALSE, sizeof(VertexData_PosTexture),
        VertexData_PosTexture::GetOffsetForPosition());
    glEnableVertexAttribArray(VertexData_PosTexture::GetIndexForPosition());

    // Texture
    glVertexAttribPointer(
        VertexData_PosTexture::GetIndexForTexture(),
        VertexData_PosTexture::GetNumberOfComponentsForTexture(), GL_FLOAT,
        GL_FALSE, sizeof(VertexData_PosTexture),
        VertexData_PosTexture::GetOffsetForTexture());
    glEnableVertexAttribArray(VertexData_PosTexture::GetIndexForTexture());
}

void Mesh::Draw() {
    glBindVertexArray(m_VAO);

    if (m_indices.size() > 0) {
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    }
}

Mesh::~Mesh() {}