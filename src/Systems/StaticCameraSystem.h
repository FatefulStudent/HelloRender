#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

class Entity;
class CameraComponent;
class TransformComponent;

class StaticCameraSystem : public System {
public:
    StaticCameraSystem();
    virtual void Initialize(Entity* entity) override;
    virtual void Update(double deltaTime, Entity* entity) override;
    virtual void Finalize(Entity* entity) override;

protected:
    void InitializeCameraComponent(CameraComponent* cameraComponent,
                                   TransformComponent* transformComponent);
    void UpdateCameraComponent(CameraComponent* cameraComponent);
    void FinalizeCameraComponent(CameraComponent* cameraComponent);
};

#endif
