#include "World.h"
#include "Entity.h"

UWorld* UWorld::World = nullptr;

UWorld* UWorld::CreateWorld() {
    World = new UWorld();
    return World;
}

void UWorld::DestroyWorld() {
    if (World) {
        World->Destroy();

        delete World;
        World = nullptr;
    }
}

UWorld* UWorld::GetWorld() {
    return World;
}

UEntity* UWorld::CreateEntity() const {
    auto NewEntity = new UEntity();
    return NewEntity;
}

UEntity* UWorld::GetFirstEntity() const {
    if (Entities.size() > 0)
        return Entities.front();

    return nullptr;
}

void UWorld::Destroy() {
    for each (UEntity* Entity in Entities) {
        delete Entity;
    }
}
