#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include <string>
#include <vector>

#include "Component.h"
#include "Helper/MeshData.h"

class UModelComponent : public UComponent {
public:
    UModelComponent(const std::string& InPath);
    virtual ~UModelComponent(){};

    std::string Path{};
    std::string DirectoryPath{};
    std::vector<FTexture> CachedTextures{};
    std::vector<FMesh> Meshes{};
};

#endif