#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"

#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <string>

class aiNode;
class aiMesh;
class aiScene;
class aiMaterial;

class Model {
public:
    Model(char* path);
    void Draw(ShaderProgram* shader);

private:
    std::vector<Texture> CachedTextures;
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat,
                                              aiTextureType type,
                                              const std::string& typeName);
};

#endif  // !MODEL_H
