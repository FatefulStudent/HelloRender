#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "System.h"

class UEntity;
class UComponent;
class UTextureComponent;
class UMeshComponent;

class URenderSystem : public USystem {
public:
    virtual void Initialize(UEntity* Entity);

    virtual void Update(UEntity* Entity);
    virtual void Finalize(UEntity* Entity);

private:
    static void InitializeMeshComponent(UMeshComponent* MeshComponent);
    static void InitializeTextureComponent(
        UTextureComponent* TextureComponent);

    static void UpdateMeshComponent(UMeshComponent* MeshComponent);
    static void UpdateTextureComponent(UTextureComponent* TextureComponent);

    static void FinalizeMeshComponent(UMeshComponent* MeshComponent);
    static void FinalizeTextureComponent(UTextureComponent* TextureComponent);
};

#endif
