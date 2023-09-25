#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <assimp/material.h>

#include <string>

class Entity;
class Component;
class ModelComponent;
class UShaderComponent;
class aiNode;
class aiScene;
class aiMesh;

class RenderingSystem : public System {
public:
    RenderingSystem();
    virtual void Initialize(Entity* Entity) override;

    virtual void Update(double DeltaTime, Entity* Entity) override;
    virtual void Finalize(Entity* Entity) override;

private:
    static std::vector<FTexture> CachedTextures;

    void InitializeModelComponent(ModelComponent* ModelComponent);
    void LoadModel(ModelComponent* ModelComponent);
    static void ProcessNode(ModelComponent* ModelComponent,
                            aiNode* Mode,
                            const aiScene* Scene);
    static void SetupMesh(FMesh& Mesh);
    static void ConvertAssimpMesh(aiMesh* AssimpMesh,
                                  const aiScene* Scene,
                                  const std::string& DirectoryPath,
                                  FMesh& OutMesh);
    static void LoadMaterialTextures(aiMaterial* AssimpMaterial,
                                     aiTextureType AssimpTextureType,
                                     const std::string& TypeName,
                                     const std::string& DirectoryPath,
                                     std::vector<FTexture>& OutTextures);

    static unsigned int TextureFromFile(const std::string& Path,
                                        const std::string& Directory);

    static void UpdateModelComponent(ModelComponent* modelComponent,
                                     UShaderComponent* shaderComponent);
   
    static void FinalizeModelComponent(ModelComponent* ModelComponent);
};

#endif
