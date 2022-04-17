#include "RenderSystem.h"
#include "Entity/Entity.h"
#include "Components/MeshComponent.h"
#include "Components/TextureComponent.h"

#include <stb_image.h>
#include <iostream>
/*
namespace {
void CreateSphere(std::vector<VertexData_PosNormalTexture>& m_vertices,
                  std::vector<Index>& m_indices) {
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

            m_vertices.push_back({{xPos, yPos, zPos},
                                  {xPos, yPos, zPos},
                                  {xSegment, ySegment}});
            m_indices.push_back({(y + 1) * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x + 1});
            m_indices.push_back({(y + 1) * (xSegments + 1) + x,
                                 y * (xSegments + 1) + x + 1,
                                 (y + 1) * (xSegments + 1) + x + 1});
        }
    }
}

}  // namespace

void URenderSystem::Initialize(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();
    assert(MeshComponent);
    if (!MeshComponent)
        return;
    InitializeMeshComponent(MeshComponent);

    UTextureComponent* TextureComponent =
        Entity->GetComponentOfClass<UTextureComponent>();
    assert(TextureComponent);
    if (!TextureComponent)
        return;
    InitializeTextureComponent(TextureComponent);
}

void URenderSystem::InitializeMeshComponent(UMeshComponent* MeshComponent) {
    if (!MeshComponent)
        return;

    CreateSphere(MeshComponent->m_vertices, MeshComponent->m_indices);

    glGenVertexArrays(1, &(MeshComponent->m_VAO));
    glBindVertexArray(MeshComponent->m_VAO);

    glGenBuffers(1, &(MeshComponent->m_VBO));
    glBindBuffer(GL_ARRAY_BUFFER, MeshComponent->m_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
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

void URenderSystem::InitializeTextureComponent(
    UTextureComponent* TextureComponent) {
    if (!TextureComponent)
        return;

    glGenTextures(1, &TextureComponent->ID);
    glBindTexture(GL_TEXTURE_2D, TextureComponent->ID);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    TextureComponent->TextureWrappingS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    TextureComponent->TextureWrappingT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    TextureComponent->TextureMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    TextureComponent->TextureMinFilter);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(TextureComponent->Path.data(), &width,
                                    &height, &nrChannels, 0);
    if (data) {
        GLenum inputImageType = 0;
        if (nrChannels == 4) {
            inputImageType = GL_RGBA;
        } else if (nrChannels == 3) {
            inputImageType = GL_RGB;
        } else {
            stbi_image_free(data);
            throw -1;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     inputImageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture at path \""
                  << TextureComponent->Path << "\"" << std::endl;
        throw -1;
    }
}

void URenderSystem::Update(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();
    assert(MeshComponent);
    if (!MeshComponent)
        return;
    UpdateMeshComponent(MeshComponent);

    
    UTextureComponent* TextureComponent =
        Entity->GetComponentOfClass<UTextureComponent>();
    assert(TextureComponent);
    if (!TextureComponent)
        return;
    UpdateTextureComponent(TextureComponent);
}

void URenderSystem::UpdateMeshComponent(UMeshComponent* MeshComponent) {
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

void URenderSystem::UpdateTextureComponent(
    UTextureComponent* TextureComponent) {
    if (!TextureComponent)
        return;

    glBindTexture(GL_TEXTURE_2D, TextureComponent->ID);
}

void URenderSystem::Finalize(UEntity* Entity) {
    if (!Entity)
        return;

    UMeshComponent* MeshComponent =
        Entity->GetComponentOfClass<UMeshComponent>();
    assert(MeshComponent);
    if (!MeshComponent)
        return;
    FinalizeMeshComponent(MeshComponent);

    UTextureComponent* TextureComponent =
        Entity->GetComponentOfClass<UTextureComponent>();
    assert(TextureComponent);
    if (!TextureComponent)
        return;
    FinalizeTextureComponent(TextureComponent);
}

void URenderSystem::FinalizeMeshComponent(UMeshComponent* MeshComponent) {
    if (!MeshComponent)
        return;

    glDeleteVertexArrays(1, &(MeshComponent->m_VAO));
    glDeleteBuffers(1, &(MeshComponent->m_EBO));
    glDeleteBuffers(1, &(MeshComponent->m_VBO));
}

void URenderSystem::FinalizeTextureComponent(
    UTextureComponent* TextureComponent) {
    if (!TextureComponent)
        return;

    // TODO: maybe do some cleanup here?
}
*/