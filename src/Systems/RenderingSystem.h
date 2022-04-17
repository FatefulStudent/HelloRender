#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <assimp/material.h>

#include <string>

class UEntity;
class UComponent;
class UModelComponent;
class UShaderComponent;
class aiNode;
class aiScene;
class aiMesh;

class URenderingSystem : public USystem {
public:
    virtual void Initialize(UEntity* Entity);

    virtual void Update(UEntity* Entity);
    virtual void Finalize(UEntity* Entity);

private:
    static std::vector<FTexture> CachedTextures;

    void InitializeModelComponent(UModelComponent* ModelComponent);
    void LoadModel(UModelComponent* ModelComponent);
    static void ProcessNode(UModelComponent* ModelComponent,
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

    static void UpdateModelComponent(UModelComponent* ModelComponent,
                                     UShaderComponent* ShaderComponent);
   
    static void FinalizeModelComponent(UModelComponent* ModelComponent);
    static void FinalizeMesh(const FMesh& Mesh);
};

#endif
