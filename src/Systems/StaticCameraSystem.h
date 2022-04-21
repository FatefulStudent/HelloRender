#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class UEntity;
class UCameraComponent;
class UTransformComponent;

class UStaticCameraSystem : public USystem {
public:
    UStaticCameraSystem();
    virtual void Initialize(UEntity* Entity) override;
    virtual void Update(float DeltaTime, UEntity* Entity) override;
    virtual void Finalize(UEntity* Entity) override;

protected:
    void InitializeCameraComponent(UCameraComponent* CameraComponent,
                                   UTransformComponent* TransformComponent);
    void UpdateCameraComponent(UCameraComponent* CameraComponent);
    void FinalizeCameraComponent(UCameraComponent* CameraComponent);
};

#endif
