#include "RenderingSystem.h"
#include "Components/ModelComponent.h"
#include "Components/ShaderComponent.h"
#include "Entity/Entity.h"
#include "Helper/ShaderHelper.h"

#include <GL/glew.h>
#include <stb_image.h>
#include <iostream>

#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

std::vector<FTexture> RenderingSystem::CachedTextures = {};

RenderingSystem::RenderingSystem() {
    requiredComponentClasses.push_back(EComponentClass::modelComponent);
    requiredComponentClasses.push_back(EComponentClass::shaderComponent);
}

void RenderingSystem::Initialize(Entity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    ModelComponent* modelComponent =
        Entity->GetComponentOfClass<ModelComponent>();
    assert(modelComponent);
    if (!modelComponent)
        return;
    InitializeModelComponent(modelComponent);
}

void RenderingSystem::InitializeModelComponent(
    ModelComponent* modelComponent) {
    if (!modelComponent) {
        assert(false);
        return;
    }
    LoadModel(modelComponent);
}

void RenderingSystem::LoadModel(ModelComponent* ModelComponent) {
    if (!ModelComponent) {
        assert(false);
        return;
    }
    stbi_set_flip_vertically_on_load(true);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(
        ModelComponent->path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        assert(false);
        return;
    }
    ModelComponent->directoryPath =
        ModelComponent->path.substr(0, ModelComponent->path.find_last_of('/'));

    ProcessNode(ModelComponent, scene->mRootNode, scene);
}

void RenderingSystem::ProcessNode(ModelComponent* ModelComponent,
                                   aiNode* Node,
                                   const aiScene* Scene) {
    if (!ModelComponent || !Node || !Scene) {
        assert(false);
        return;
    }

    ModelComponent->meshes.reserve(Node->mNumMeshes);
    
    // process all the node's meshes (if any)
    for (size_t i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* AssimpMesh = Scene->mMeshes[Node->mMeshes[i]];
        FMesh NewMesh;
        ConvertAssimpMesh(AssimpMesh, Scene, ModelComponent->directoryPath,
                          NewMesh);
        ModelComponent->meshes.push_back(std::move(NewMesh));
    }
    // then do the same for each of its children
    for (size_t i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(ModelComponent, Node->mChildren[i], Scene);
    }
}

void RenderingSystem::SetupMesh(FMesh& Mesh) {
    if (Mesh.bMeshIsSetup) {
        assert(false);
        return;
    }

    // create buffers/arrays
    glGenVertexArrays(1, &(Mesh.VAO));
    glGenBuffers(1, &(Mesh.VBO));
    glGenBuffers(1, &(Mesh.EBO));

    glBindVertexArray(Mesh.VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, Mesh.VBO);
    // A great thing about structs is that their memory layout is
    // sequential for all its items. The effect is that we can simply pass
    // a pointer to the struct and it translates perfectly to a glm::vec3/2
    // array which again translates to 3/2 floats which translates to a
    // byte array.
    glBufferData(GL_ARRAY_BUFFER, Mesh.Vertices.size() * sizeof(FVertex),
                 &Mesh.Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 Mesh.Indices.size() * sizeof(unsigned int), &Mesh.Indices[0],
                 GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex),
                          (void*)offsetof(FVertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex),
                          (void*)offsetof(FVertex, TexCoords));
    glBindVertexArray(0);

    Mesh.bMeshIsSetup = true;
}

void RenderingSystem::ConvertAssimpMesh(aiMesh* AssimpMesh,
                                         const aiScene* Scene,
                                         const std::string& DirectoryPath,
                                         FMesh& OutMesh) {
    if (!AssimpMesh || !Scene) {
        assert(false);
        return;
    }

    std::vector<FVertex>& Vertices = OutMesh.Vertices;
    std::vector<unsigned int>& Indices = OutMesh.Indices;
    std::vector<FTexture>& Textures = OutMesh.Textures;

    for (size_t i = 0; i < AssimpMesh->mNumVertices; i++) {
        const auto CurrentAiVertex = AssimpMesh->mVertices[i];
        FVertex Vertex = {};
        // process vertex positions, normals and texture coordinates
        Vertex.Location = {AssimpMesh->mVertices[i].x,
                           AssimpMesh->mVertices[i].y,
                           AssimpMesh->mVertices[i].z};
        if (AssimpMesh->HasNormals())
            Vertex.Normal = {AssimpMesh->mNormals[i].x,
                             AssimpMesh->mNormals[i].y,
                             AssimpMesh->mNormals[i].z};
        if (AssimpMesh->mTextureCoords[0])
            Vertex.TexCoords = {AssimpMesh->mTextureCoords[0][i].x,
                                AssimpMesh->mTextureCoords[0][i].y};
        else
            Vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        Vertices.push_back(Vertex);
    }

    // process indices
    for (size_t i = 0; i < AssimpMesh->mNumFaces; i++) {
        aiFace face = AssimpMesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices
        // vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            Indices.push_back(face.mIndices[j]);
    }

    // process materials
    if (AssimpMesh->mMaterialIndex >= 0) {
        aiMaterial* Material = Scene->mMaterials[AssimpMesh->mMaterialIndex];

        std::vector<FTexture> DiffuseMaps;
        LoadMaterialTextures(Material, aiTextureType_DIFFUSE,
                             "texture_diffuse", DirectoryPath, DiffuseMaps);
        if (!DiffuseMaps.empty()) {
            Textures.insert(Textures.end(), DiffuseMaps.begin(),
                           DiffuseMaps.end());
        }

        std::vector<FTexture> SpecularMaps;
        LoadMaterialTextures(Material, aiTextureType_SPECULAR,
                             "texture_specular", DirectoryPath, SpecularMaps);
        if (!SpecularMaps.empty()) {
            Textures.insert(Textures.end(), SpecularMaps.begin(),
                            SpecularMaps.end());
        }
    }

    SetupMesh(OutMesh);
}

void RenderingSystem::LoadMaterialTextures(
    aiMaterial* Material,
    aiTextureType TextureType,
    const std::string& TypeName,
    const std::string& DirectoryPath,
    std::vector<FTexture>& OutTextures) {
    if (!Material) {
        assert(false);
        return;
    }
    for (size_t i = 0; i < Material->GetTextureCount(TextureType); i++) {
        aiString PathString;
        Material->GetTexture(TextureType, i, &PathString);
        bool bSkip = false;

        for (unsigned int j = 0; j < CachedTextures.size(); j++) {
            const bool bTextureWasAlreadyLoaded =
                CachedTextures[j].Path == std::string(PathString.C_Str());
            if (bTextureWasAlreadyLoaded) {
                OutTextures.push_back(CachedTextures[j]);
                bSkip = true;
                break;
            }
        }

        if (!bSkip) {  // if texture hasn't been loaded already, load it
            FTexture Texture;
            Texture.ID = TextureFromFile(std::string(PathString.C_Str()),
                                         DirectoryPath);
            Texture.Type = TypeName;
            Texture.Path = PathString.C_Str();
            OutTextures.push_back(Texture);
            CachedTextures.push_back(Texture);  // add to loaded textures
        }
    }
}

unsigned int RenderingSystem::TextureFromFile(const std::string& Path,
                                               const std::string& Directory) {
    stbi_set_flip_vertically_on_load(true);
    std::string Filename = Directory + '/' + Path;

    unsigned int TextureID;
    glGenTextures(1, &TextureID);

    int Width, Height, NumberOfComponents;
    unsigned char* Data =
        stbi_load(Filename.c_str(), &Width, &Height, &NumberOfComponents, 0);
    if (Data) {
        GLenum Format = 0;
        if (NumberOfComponents == 1)
            Format = GL_RED;
        else if (NumberOfComponents == 3)
            Format = GL_RGB;
        else if (NumberOfComponents == 4)
            Format = GL_RGBA;
        else {
            assert(false);
            return 0;
        }

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format,
                     GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // TODO: make them to be configurable?
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(Data);
    } else {
        std::cerr << "Texture failed to load at path: " << Path << std::endl;
        assert(false);
        stbi_image_free(Data);
    }

    return TextureID;
}

void RenderingSystem::Update(double DeltaTime, Entity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UShaderComponent* ShaderComponent =
        Entity->GetComponentOfClass<UShaderComponent>();
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    ModelComponent* modelComponent =
        Entity->GetComponentOfClass<ModelComponent>();
    if (!modelComponent) {
        assert(false);
        return;
    }

    UpdateModelComponent(modelComponent, ShaderComponent);
}

void DrawMesh(const FMesh& Mesh, UShaderComponent* ShaderComponent) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }
    glUseProgram(ShaderComponent->ShaderProgramID);

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    if (Mesh.Textures.empty()) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    for (unsigned int i = 0; i < Mesh.Textures.size(); i++) {
        // activate proper texture unit before binding
        glActiveTexture(GL_TEXTURE0 + i);

        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = Mesh.Textures[i].Type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        ShaderHelper::SetFloat(ShaderComponent->ShaderProgramID,
                               ("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, Mesh.Textures[i].ID);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(Mesh.VAO);
    glDrawElements(GL_TRIANGLES, Mesh.Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RenderingSystem::UpdateModelComponent(
    ModelComponent* modelComponent,
    UShaderComponent* shaderComponent) {
    if (!modelComponent) {
        assert(false);
        return;
    }

    if (!shaderComponent) {
        assert(false);
        return;
    }

    for (const FMesh& mesh : modelComponent->meshes)
        DrawMesh(mesh, shaderComponent);
}

void RenderingSystem::Finalize(Entity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    ModelComponent* modelComponent =
        Entity->GetComponentOfClass<ModelComponent>();
    if (!modelComponent) {
        assert(false);
        return;
    }
    FinalizeModelComponent(modelComponent);
}

void RenderingSystem::FinalizeModelComponent(
    ModelComponent* ModelComponent) {
    if (!ModelComponent) {
        assert(false);
        return;
    }
    ModelComponent->meshes.clear();
}
