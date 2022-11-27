#include "World.h"
#include "Entity/Entity.h"
#include "Systems/System.h"

#include <algorithm>

UWorld* UWorld::World = nullptr;
UEntity* UWorld::LocalPlayer = nullptr;

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

std::vector<UEntity*> UWorld::GetAllEntitiesWithComponents(
    const std::vector<EComponentClass>& RequiredClasses) const {
    std::vector<UEntity*> Result{};

    for (UEntity* Entity : Entities) {
        if (Entity) {
            const std::unordered_map<EComponentClass, UComponent*>&
                ClassesToComponents = Entity->ComponentClassToComponent;

            bool bHasAllClasses = true;
            for (EComponentClass ComponentClass : RequiredClasses) {
                const bool bContains =
                    ClassesToComponents.find(ComponentClass) !=
                    ClassesToComponents.end();

                if (!bContains) {
                    bHasAllClasses = false;
                    break;
                }
            }

            if (bHasAllClasses)
                Result.push_back(Entity);
        }
    }
    return Result;
}

void UWorld::Initialize() const {
    for (USystem* System : Systems) {
        InitializeSystem(System);
    }
}

void UWorld::InitializeSystem(USystem* System) const {
    if (!System)
        return;
    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for (UEntity* Entity : ValidEntities) {
        System->Initialize(Entity);
    }
}

void UWorld::Update(float DeltaTime) const{
    for (USystem* System : Systems) {
        UpdateSystem(DeltaTime, System);
    }
}

void UWorld::UpdateSystem(float DeltaTime, USystem* System) const {
    if (!System)
        return;

    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for (UEntity* Entity : ValidEntities) {
        System->Update(DeltaTime, Entity);
    }
}

void UWorld::Finalize() const {
    for (USystem* System : Systems) {
        FinalizeSystem(System);
    }
}

void UWorld::FinalizeSystem(USystem* System) const {
    if (!System)
        return;
    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for (UEntity* Entity : ValidEntities) {
        System->Finalize(Entity);
    }
}


UEntity* UWorld::CreateEntity(const std::string& InEntityName) {
    auto* NewEntity = new UEntity(InEntityName);
    Entities.push_back(NewEntity);
    return NewEntity;
}

void UWorld::DestroyEntity(UEntity* Entity) {
    if (!Entity)
        return;

    DestroyEntityImpl(Entity);

    auto EntityIter = std::find(Entities.begin(), Entities.end(), Entity);
    if (EntityIter != Entities.end())
        Entities.erase(EntityIter);
    delete Entity;
}

void UWorld::Destroy() {
    for (UEntity* Entity : Entities) {
        if (Entity) {
            DestroyEntityImpl(Entity);
            delete Entity;
        }
    }
    Entities.clear();

    for (USystem* System : Systems) {
        delete System;
    }
    Systems.clear();
}

void UWorld::DestroyEntityImpl(UEntity* Entity) {
    if (!Entity)
        return;

    Entity->DestroyImpl();
}
