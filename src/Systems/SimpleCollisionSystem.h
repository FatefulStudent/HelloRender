#ifndef SIMPLE_COLLISION_SYSTEM_H
#define SIMPLE_COLLISION_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class UEntity;
class USimpleCollisionComponent;
class UMovementComponent;
class UTransformComponent;

class USimpleCollisionSystem : public USystem {
public:
    USimpleCollisionSystem();
    virtual void Update(float DeltaTime, UEntity* Entity) override;

protected:
    static void CheckBorders(const USimpleCollisionComponent* CollisionComponent,
                      UMovementComponent* MovementComponent,
                      const UTransformComponent* TransformComponent);
};

#endif
