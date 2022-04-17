#include "Model.h"
#include "shaderProgram.h"
#include "World/World.h"
#include "Components/ShaderComponent.h"
#include "Entity/Entity.h"

#include <stb_image.h>

namespace {
unsigned int TextureFromFile(const char* path, const std::string& directory) {
    std::string filename(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data =
        stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = NULL;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}  // namespace
}  // namespace


Model::Model(char* path) {
    LoadModel(path);
}

void Model::Draw(UShaderComponent* ShaderComponent) {
    for (unsigned int i = 0; i < meshes.size(); i++) {

        meshes[i].Draw(ShaderComponent); 
    }
}

void Model::LoadModel(const std::string& path) {

    stbi_set_flip_vertically_on_load(true);

    Assimp::Importer import;
    const aiScene* scene =
        import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<FVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<FTexture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        const auto CurrentAiVertex = mesh->mVertices[i];
        FVertex vertex = {};
        // process vertex positions, normals and texture coordinates
        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y,
                           mesh->mVertices[i].z};
        if (mesh->HasNormals())
            vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y,
                             mesh->mNormals[i].z};
        if (mesh->mTextureCoords[0])
            vertex.TexCoords = {mesh->mTextureCoords[0][i].x,
                                mesh->mTextureCoords[0][i].y};
        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices
        // vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<FTexture> diffuseMaps = LoadMaterialTextures(
            material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(),
                        diffuseMaps.end());
        std::vector<FTexture> specularMaps = LoadMaterialTextures(
            material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<FTexture> Model::LoadMaterialTextures(aiMaterial* mat,
                                                 aiTextureType type,
                                                 const std::string& typeName) {
    std::vector<FTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < CachedTextures.size(); j++) {
            const bool bTextureWasAlreadyLoaded =
                CachedTextures[j].Path == std::string(str.C_Str());
            if (bTextureWasAlreadyLoaded) {
                textures.push_back(CachedTextures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {  // if texture hasn't been loaded already, load it
            FTexture texture;
            texture.ID = TextureFromFile(str.C_Str(), directory);
            texture.Type = typeName;
            texture.Path = str.C_Str();
            textures.push_back(texture);
            CachedTextures.push_back(texture);  // add to loaded textures
        }
    }
    return textures;
}
