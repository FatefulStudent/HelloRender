#include "ShaderSystem.h"
#include "Components/ShaderComponent.h"
#include "Entity/Entity.h"
#include "Helper/FileHelper.h"
#include "Helper/ShaderData.h"
#include "Helper/ShaderHelper.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>

void UShaderSystem::Initialize(UEntity* Entity) {
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

void UShaderSystem::InitializeShaderComponent(
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
    ShaderComponent->ID = glCreateProgram();
    glAttachShader(ShaderComponent->ID, VertexShader.ID);
    glAttachShader(ShaderComponent->ID, FragmentShader.ID);
    glLinkProgram(ShaderComponent->ID);

    static int success;
    static char infoLog[512];

    glGetProgramiv(ShaderComponent->ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderComponent->ID, 512, NULL, infoLog);
        std::cerr << "ERROR::UShaderSystem::InitializeShaderComponent::"
                     "LINKING_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

void UShaderSystem::LoadShader(const std::string& Path,
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

EShaderType UShaderSystem::GetShaderTypeFromPath(
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

void UShaderSystem::Update(UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UShaderComponent* ShaderComponent =
        Entity->GetComponentOfClass<UShaderComponent>();
    assert(ShaderComponent);
    if (!ShaderComponent)
        return;
    UpdateShaderComponent(ShaderComponent);
}

void UShaderSystem::UpdateShaderComponent(UShaderComponent* ShaderComponent) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    glUseProgram(ShaderComponent->ID);

    ShaderHelper::SetMatrix(ShaderComponent, "Model", ShaderComponent->Model);
    ShaderHelper::SetMatrix(ShaderComponent, "View", ShaderComponent->View);
    ShaderHelper::SetMatrix(ShaderComponent, "Projection",
                            ShaderComponent->Projection);
}

void UShaderSystem::Finalize(UEntity* Entity) {
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

void UShaderSystem::FinalizeShaderComponent(
    UShaderComponent* ShaderComponent) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    // TODO: some kind of clearing up?
}
