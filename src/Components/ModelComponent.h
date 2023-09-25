#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "Component.h"
#include "Helper/MeshData.h"

#include <string>
#include <vector>

class ModelComponent : public Component {
public:
    explicit ModelComponent(std::string inPath);
    virtual ~ModelComponent() = default;

    std::string path{};
    std::string directoryPath{};
    std::vector<FTexture> cachedTextures{};
    std::vector<FMesh> meshes{};
};

#endif