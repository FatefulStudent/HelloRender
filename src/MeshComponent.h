#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include <string>
#include <vector>

#include "Component.h"
#include "Helper/VertexData.h"

class UMeshComponent : public UComponent {

public:
    virtual void Destroy(){};

    virtual ~UMeshComponent(){};

    std::vector<VertexData_PosNormalTexture> m_vertices = {};
    std::vector<Index> m_indices = {};
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    unsigned int m_EBO = 0;

private:
    std::string TexturePath = "";
    float Radius = 1.0f;
};

#endif