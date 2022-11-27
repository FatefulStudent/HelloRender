#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/glm.hpp>

#include <string>
#include <vector>

struct FVertex {
    glm::vec3 Location;
    glm::vec3 Normal;
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