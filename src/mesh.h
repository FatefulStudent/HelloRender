#ifndef MESH_H
#define MESH_H

#include "Helper/VertexData.h"

#include <vector>

class Mesh {
private:
    std::vector<VertexData_PosTexture> m_vertices = {};
    std::vector<Index> m_indices = {};
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

public:
    Mesh();
    ~Mesh();

    void Draw();
};

#endif
