#ifndef SIMPLE_COLLISION_SYSTEM_H
#define SIMPLE_COLLISION_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class Entity;
class SimpleCollisionComponent;
class MovementComponent;
class TransformComponent;

class SimpleCollisionSystem : public System {
public:
    SimpleCollisionSystem();
    virtual void Update(double DeltaTime, Entity* Entity) override;

protected:
    static void CheckBorders(const SimpleCollisionComponent* collisionComponent,
                      MovementComponent* movementComponent,
                      const TransformComponent* transformComponent);
};

#endif
