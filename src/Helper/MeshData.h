#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/glm.hpp>

#include <string>
#include <vector>

struct FVertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
};

struct FTexture {
    unsigned int ID = 0;
    std::string Type{};
    std::string Path{};
};

struct FMesh {
    FMesh() = default;
    // sometimes there are >15000 vertices and indeces. We should never copy them. 
    FMesh(const FMesh& Other) = delete;
    FMesh(FMesh&& Other) noexcept;
    ~FMesh();
    std::vector<FVertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<FTexture> Textures;

    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    bool bMeshIsSetup = false;
};

#endif