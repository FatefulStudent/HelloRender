#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "Helper/MeshData.h"
#include "System.h"

#include <string>

class Entity;
class MovementComponent;
class TransformComponent;

class MovementSystem : public System {
public:
    MovementSystem();
    virtual void Update(double deltaTime, Entity* entity) override;

protected: 
    static void UpdateTransformComponent(
        double deltaTime,
        const MovementComponent* movementComponent,
        TransformComponent* transformComponent);
};

#endif
