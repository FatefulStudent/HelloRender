#include "ShaderSystem.h"
#include "Components/ShaderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Entity/Entity.h"
#include "Helper/FileHelper.h"
#include "Helper/ShaderData.h"
#include "Helper/ShaderHelper.h"

#include "World/World.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace
{

}

ShaderSystem::ShaderSystem() {
    requiredComponentClasses.push_back(EComponentClass::shaderComponent);
    requiredComponentClasses.push_back(EComponentClass::transformComponent);
}

void ShaderSystem::Initialize(Entity* Entity) {
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
    InitializeShaderComponent(ShaderComponent);
}

void ShaderSystem::InitializeShaderComponent(
    UShaderComponent* ShaderComponent) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    FShaderData VertexShader;
    LoadShader(ShaderComponent->VertexShaderPath, VertexShader);
    assert(VertexShader.ShaderType == EShaderType::Vertex);

    FShaderData FragmentShader;
    LoadShader(ShaderComponent->FragmentShaderPath, FragmentShader);
    assert(FragmentShader.ShaderType == EShaderType::Fragment);

    // shader Program
    ShaderComponent->ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderComponent->ShaderProgramID, VertexShader.ID);
    glAttachShader(ShaderComponent->ShaderProgramID, FragmentShader.ID);
    glLinkProgram(ShaderComponent->ShaderProgramID);

    static int success;
    static char infoLog[512];

    glGetProgramiv(ShaderComponent->ShaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderComponent->ShaderProgramID, 512, NULL,
                            infoLog);
        std::cerr << "ERROR::UShaderSystem::InitializeShaderComponent::"
                     "LINKING_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

void ShaderSystem::LoadShader(const std::string& Path,
                               FShaderData& OutShader) {
    static char infoLog[512];

    if (Path.empty()) {
        std::cerr << "ERROR::UShaderSystem::LoadShader shaderPath is NULL.\n"
                  << std::endl;
        throw -1;
    }

    OutShader.ShaderType = GetShaderTypeFromPath(Path);

    if (OutShader.ShaderType == EShaderType::Undefined) {
        std::cerr
            << "ERROR::UShaderSystem::LoadShader ShaderType is Undefined.\n"
            << std::endl;
        throw -1;
    }

    auto GLShaderTypeIter =
        FShaderData::ShaderTypeToGLShaderType.find(OutShader.ShaderType);

    if (GLShaderTypeIter == FShaderData::ShaderTypeToGLShaderType.end()) {
        std::cerr << "ERROR::UShaderSystem::LoadShader GLShaderType for "
                     "ShaderType "
                  << static_cast<uint8_t>(OutShader.ShaderType)
                  << " is not found in ShaderTypeToGLShaderType Map.\n"
                  << std::endl;
        throw -1;
    }

    std::string shaderString = FileHelper::ReadFile(Path);
    const char* shaderSource = shaderString.c_str();

    OutShader.GLShaderType = GLShaderTypeIter->second;

    OutShader.ID = glCreateShader(OutShader.GLShaderType);
    glShaderSource(OutShader.ID, 1, &shaderSource, NULL);
    glCompileShader(OutShader.ID);

    int success;
    glGetShaderiv(OutShader.ID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(OutShader.ID, 512, NULL, infoLog);
        std::cerr << "ERROR::UShaderSystem::LoadShader::"
                  << static_cast<uint8_t>(OutShader.ShaderType)
                  << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

EShaderType ShaderSystem::GetShaderTypeFromPath(
    const std::string& ShaderPath) {
    const std::string FileExtension =
        FileHelper::GetExtensionFromFileName(ShaderPath);

    const auto MatchingShaderType =
        FShaderData::FileExtensionToShaderType.find(FileExtension);

    if (MatchingShaderType == FShaderData::FileExtensionToShaderType.end())
        return EShaderType::Undefined;
    else
        return MatchingShaderType->second;
}

void ShaderSystem::Update(double DeltaTime, Entity* Entity) {
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

    TransformComponent* transformComponent =
        Entity->GetComponentOfClass<TransformComponent>();
    if (!transformComponent) {
        assert(false);
        return;
    }

    UpdateShaderComponent(ShaderComponent, transformComponent);
}

void ShaderSystem::UpdateShaderComponent(
    UShaderComponent* shaderComponent,
    TransformComponent* transformComponent) {
    if (!shaderComponent) {
        assert(false);
        return;
    }

    if (!transformComponent) {
        assert(false);
        return;
    }

    
    glUseProgram(shaderComponent->ShaderProgramID);

    ShaderHelper::SetMatrix(shaderComponent->ShaderProgramID, "Model",
                            transformComponent->GetTransformMatrix());

    World* world = World::GetWorld();
    Entity* playerEntity = world->localPlayer;
    CameraComponent* playerCamera =
        playerEntity->GetComponentOfClass<CameraComponent>();

    ShaderHelper::SetMatrix(shaderComponent->ShaderProgramID, "View",
                            playerCamera->view);
    ShaderHelper::SetMatrix(shaderComponent->ShaderProgramID, "Projection",
                            playerCamera->projection);
}

void ShaderSystem::Finalize(Entity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UShaderComponent* ShaderComponent =
        Entity->GetComponentOfClass<UShaderComponent>();
    assert(ShaderComponent);
    if (!ShaderComponent)
        return;
    FinalizeShaderComponent(ShaderComponent);
}

void ShaderSystem::FinalizeShaderComponent(
    UShaderComponent* ShaderComponent) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    // TODO: some kind of clearing up?
}
