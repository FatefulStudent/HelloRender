#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class Entity;
class UShaderComponent;
class TransformComponent;
struct FShaderData;
enum class EShaderType : uint8_t;

class ShaderSystem : public System {
public:
    ShaderSystem();
    virtual void Initialize(Entity* Entity) override;
    virtual void Update(double DeltaTime, Entity* Entity) override;
    virtual void Finalize(Entity* Entity) override;

private:
    static void InitializeShaderComponent(UShaderComponent* ShaderComponent);
    static void LoadShader(const std::string& Path, FShaderData& OutShader);
    static EShaderType GetShaderTypeFromPath(const std::string& ShaderPath);

    static void UpdateShaderComponent(
        UShaderComponent* shaderComponent,
        TransformComponent* TransformComponent);
    static void FinalizeShaderComponent(UShaderComponent* ShaderComponent);
};

#endif
