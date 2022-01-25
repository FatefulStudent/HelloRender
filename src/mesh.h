#ifndef MESH_H
#define MESH_H

#include "Helper/VertexData.h"

#include <vector>

class Mesh {
private:
    std::vector<VertexData_PosColorTexture> m_vertices;
    std::vector<unsigned> m_indices;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

public:
    Mesh(std::vector<VertexData_PosColorTexture>&& vertexData,
         std::vector<unsigned>&& indexData);
    ~Mesh();

    void Draw();
};

#endif
