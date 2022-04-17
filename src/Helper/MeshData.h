#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/glm.hpp>

#include <string>
#include <vector>

class ShaderProgram;

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
    std::vector<FVertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<FTexture> Textures;
    unsigned int VAO, VBO, EBO;

    bool bMeshIsSetup = false;
};

#endif