#include "mesh.h"

#include <GL/glew.h>

Mesh::Mesh(const std::vector<VertexData_PosColorTexture>& vertexData,
           const std::vector<Vector3<unsigned>>& indexData) {
    m_indices = indexData;
    m_vertices = vertexData;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(Vector3<unsigned>),
                 m_indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(VertexData_PosColorTexture),
                 m_vertices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(
        VertexData_PosColorTexture::GetIndexForPosition(),
        VertexData_PosColorTexture::GetNumberOfComponentsForPosition(),
        GL_FLOAT, GL_FALSE, sizeof(VertexData_PosColorTexture),
        VertexData_PosColorTexture::GetOffsetForPosition());
    glEnableVertexAttribArray(
        VertexData_PosColorTexture::GetIndexForPosition());

    // Color
    glVertexAttribPointer(
        VertexData_PosColorTexture::GetIndexForColor(),
        VertexData_PosColorTexture::GetNumberOfComponentsForColor(), GL_FLOAT,
        GL_FALSE, sizeof(VertexData_PosColorTexture),
        VertexData_PosColorTexture::GetOffsetForColor());
    glEnableVertexAttribArray(VertexData_PosColorTexture::GetIndexForColor());

    // Texture
    glVertexAttribPointer(
        VertexData_PosColorTexture::GetIndexForTexture(),
        VertexData_PosColorTexture::GetNumberOfComponentsForTexture(),
        GL_FLOAT, GL_FALSE, sizeof(VertexData_PosColorTexture),
        VertexData_PosColorTexture::GetOffsetForTexture());
    glEnableVertexAttribArray(
        VertexData_PosColorTexture::GetIndexForTexture());
}

void Mesh::Draw() {
    glBindVertexArray(m_VAO);
    glDrawElements(
        GL_TRIANGLES,
        m_indices.size() * Vector3<unsigned>::GetNumberOfComponents(),
        GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh() {}