#include "Entity.h"
#include "RenderSystem.h"
#include "MeshComponent.h"

void URenderSystem::Initialize(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();
   
    assert(MeshComponent);
    if (!MeshComponent)
        return;

    constexpr float TAU = 6.2831853071;
    constexpr float PI = 3.14159265359;
    constexpr unsigned int xSegments = 30;
    constexpr unsigned int ySegments = 30;
    for (unsigned int y = 0; y <= ySegments; ++y) {
        for (unsigned int x = 0; x <= xSegments; ++x) {
            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * TAU) *
                         std::sin(ySegment * PI);  // TAU is 2PI
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);

            MeshComponent->m_vertices.push_back({{xPos, yPos, zPos},
                                  {xPos, yPos, zPos},
                                  {xSegment, ySegment}});
            MeshComponent->m_indices.push_back({(y + 1) * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x + 1});
            MeshComponent->m_indices.push_back(
                {(y + 1) * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x + 1,
                                 (y + 1) * (xSegments + 1) + x + 1});
        }
    }

    glGenVertexArrays(1, &(MeshComponent->m_VAO));
    glBindVertexArray(MeshComponent->m_VAO);

    glGenBuffers(1, &(MeshComponent->m_VBO));
    glBindBuffer(GL_ARRAY_BUFFER, MeshComponent->m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
        MeshComponent->m_vertices.size() * sizeof(VertexData_PosNormalTexture),
        MeshComponent->m_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &(MeshComponent->m_EBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshComponent->m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 MeshComponent->m_indices.size() * sizeof(Index),
                 MeshComponent->m_indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(
        VertexData_PosNormalTexture::GetIndexForPosition(),
        VertexData_PosNormalTexture::GetNumberOfComponentsForPosition(),
        GL_FLOAT, GL_FALSE, sizeof(VertexData_PosNormalTexture),
        VertexData_PosNormalTexture::GetOffsetForPosition());
    glEnableVertexAttribArray(
        VertexData_PosNormalTexture::GetIndexForPosition());

    // Normal
    glVertexAttribPointer(
        VertexData_PosNormalTexture::GetIndexForNormal(),
        VertexData_PosNormalTexture::GetNumberOfComponentsForNormal(),
        GL_FLOAT, GL_FALSE, sizeof(VertexData_PosNormalTexture),
        VertexData_PosNormalTexture::GetOffsetForNormal());
    glEnableVertexAttribArray(
        VertexData_PosNormalTexture::GetIndexForNormal());

    // Texture
    glVertexAttribPointer(
        VertexData_PosNormalTexture::GetIndexForTexture(),
        VertexData_PosNormalTexture::GetNumberOfComponentsForTexture(),
        GL_FLOAT, GL_FALSE, sizeof(VertexData_PosNormalTexture),
        VertexData_PosNormalTexture::GetOffsetForTexture());
    glEnableVertexAttribArray(
        VertexData_PosNormalTexture::GetIndexForTexture());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void URenderSystem::Update(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();

    assert(MeshComponent);
    if (!MeshComponent)
        return;

    glBindVertexArray(MeshComponent->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, MeshComponent->m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshComponent->m_EBO);

    glDrawElements(GL_TRIANGLES,
                   MeshComponent->m_indices.size() * sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void URenderSystem::Finalize(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();

    assert(MeshComponent);
    if (!MeshComponent)
        return;

    glDeleteVertexArrays(1, &(MeshComponent->m_VAO));
    glDeleteBuffers(1, &(MeshComponent->m_EBO));
    glDeleteBuffers(1, &(MeshComponent->m_VBO));
}
