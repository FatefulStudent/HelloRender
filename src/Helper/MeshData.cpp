#include "MeshData.h"

#include <GL/glew.h>

FMesh::FMesh(FMesh&& Other) noexcept
    : Vertices(std::move(Other.Vertices)),
      Indices(std::move(Other.Indices)),
      Textures(std::move(Other.Textures)),
      VAO(Other.VAO),
      EBO(Other.EBO),
      VBO(Other.VBO) {
    // NB: don't forget to unvalidate VAO, VBO, EBO so that they
    //     would not delete these buffers on destructor
    Other.VAO = 0;
    Other.EBO = 0;
    Other.VBO = 0;
}

FMesh::~FMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}
