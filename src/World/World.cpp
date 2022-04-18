#include "World.h"
#include "../Entity/Entity.h"
#include "../Systems/System.h"

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

std::vector<UEntity*> UWorld::GetAllEntitiesWithComponents(
    const std::vector<EComponentClass> RequiredClasses) const {
    std::vector<UEntity*> Result{};

    for (UEntity* Entity : Entities) {
        if (Entity) {
            const std::unordered_map<EComponentClass, UComponent*>&
                ClassesToComponents = Entity->ComponentClassToComponent;

            bool bHasAllClasses = true;
            for each (EComponentClass ComponentClass in RequiredClasses) {
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

void UWorld::Initialize() {
    for (USystem* System : Systems) {
        InitializeSystem(System);
    }
}

void UWorld::InitializeSystem(USystem* System) {
    if (!System)
        return;
    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for each (UEntity* Entity in ValidEntities) {
        System->Initialize(Entity);
    }
}

void UWorld::Update() {
    for (USystem* System : Systems) {
        UpdateSystem(System);
    }
}

void UWorld::UpdateSystem(USystem* System) {
    if (!System)
        return;

    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for each (UEntity* Entity in ValidEntities) {
        System->Update(Entity);
    }
}

void UWorld::Finalize() {
    for (USystem* System : Systems) {
        FinalizeSystem(System);
    }
}

void UWorld::FinalizeSystem(USystem* System) {
    if (!System)
        return;
    const std::vector<UEntity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for each (UEntity* Entity in ValidEntities) {
        System->Finalize(Entity);
    }
}


UEntity* UWorld::CreateEntity() {
    UEntity* NewEntity = new UEntity();
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
        if (System) {
            delete System;
        }
    }
    Systems.clear();
}

void UWorld::DestroyEntityImpl(UEntity* Entity) {
    if (!Entity)
        return;

    Entity->DestroyImpl();
}
