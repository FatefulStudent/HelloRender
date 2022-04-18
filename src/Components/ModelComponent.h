#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "Component.h"
#include "Helper/MeshData.h"

#include <string>
#include <vector>

class UModelComponent : public UComponent {
public:
    UModelComponent(const std::string& InPath);
    virtual ~UModelComponent() = default;

    std::string Path{};
    std::string DirectoryPath{};
    std::vector<FTexture> CachedTextures{};
    std::vector<FMesh> Meshes{};
};

#endif