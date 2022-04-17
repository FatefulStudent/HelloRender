#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>  // holds all OpenGL type declarations

#include <glm/glm.hpp>

#include "Helper/MeshData.h"

#include <string>
#include <vector>

class ShaderProgram;
class UShaderComponent;

class Mesh {
public:
    // mesh Data
    std::vector<FVertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<FTexture> Textures;
    unsigned int VAO;

    // constructor
    Mesh(const std::vector<FVertex>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<FTexture>& textures);

    void Draw(UShaderComponent* ShaderComponent);

    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void SetupMesh();
};

#endif