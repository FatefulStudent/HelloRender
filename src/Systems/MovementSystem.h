#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class UEntity;
class UMovementComponent;
class UTransformComponent;

class UMovementSystem : public USystem {
public:
    UMovementSystem();
    virtual void Update(float DeltaTime, UEntity* Entity) override;

protected: 
    void UpdateMovementComponent(
        UMovementComponent* MovementComponent,
        const UTransformComponent* TransformComponent);
    void UpdateTransformComponent(
        float DeltaTime,
        const UMovementComponent* MovementComponent,
        UTransformComponent* TransformComponent);
};

#endif
