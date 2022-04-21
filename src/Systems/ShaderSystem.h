#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class UEntity;
class UShaderComponent;
class UTransformComponent;
struct FShaderData;
enum class EShaderType : uint8_t;

class UShaderSystem : public USystem {
public:
    UShaderSystem();
    virtual void Initialize(UEntity* Entity) override;
    virtual void Update(float DeltaTime, UEntity* Entity) override;
    virtual void Finalize(UEntity* Entity) override;

private:
    static void InitializeShaderComponent(UShaderComponent* ShaderComponent);
    static void LoadShader(const std::string& Path, FShaderData& OutShader);
    static EShaderType GetShaderTypeFromPath(const std::string& ShaderPath);

    static void UpdateShaderComponent(
        UShaderComponent* ShaderComponent,
        const UTransformComponent* TransformComponent);
    static void FinalizeShaderComponent(UShaderComponent* ShaderComponent);
};

#endif
