#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <string>

class aiNode;
class aiMesh;
class aiScene;
class aiMaterial;
class ShaderComponent;

class Model {
public:
    Model(char* path);
    void Draw(UShaderComponent* ShaderComponent);

    std::vector<FTexture> CachedTextures;
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<FTexture> LoadMaterialTextures(aiMaterial* mat,
                                              aiTextureType type,
                                              const std::string& typeName);
};

#endif  // !MODEL_H
