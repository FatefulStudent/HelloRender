#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class UEntity;
class UShaderComponent;
struct FShaderData;
enum class EShaderType : uint8_t;

class UShaderSystem : public USystem {
public:
    virtual void Initialize(UEntity* Entity);
    virtual void Update(UEntity* Entity);
    virtual void Finalize(UEntity* Entity);

private:
    static void InitializeShaderComponent(UShaderComponent* ShaderComponent);
    static void LoadShader(const std::string& Path, FShaderData& OutShader);
    static EShaderType GetShaderTypeFromPath(const std::string& ShaderPath);

    static void UpdateShaderComponent(UShaderComponent* ShaderComponent);
    static void FinalizeShaderComponent(UShaderComponent* ShaderComponent);
};

#endif
