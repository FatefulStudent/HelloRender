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

void UWorld::Initialize() {
    for (USystem* System : Systems) {
        InitializeSystem(System);
    }
}

void UWorld::InitializeSystem(USystem* System) {
    if (!System)
        return;

    System->Initialize(GetFirstEntity());
}

void UWorld::Update() {
    for (USystem* System : Systems) {
        UpdateSystem(System);
    }
}

void UWorld::UpdateSystem(USystem* System) {
    if (!System)
        return;

    System->Update(GetFirstEntity());
}

void UWorld::Finalize() {
    for (USystem* System : Systems) {
        FinalizeSystem(System);
    }
}

void UWorld::FinalizeSystem(USystem* System) {
    if (!System)
        return;

    System->Finalize(GetFirstEntity());
}

USystem* UWorld::GetFirstSystem() const {
    if (Systems.size() > 0)
        return Systems.front();

    return nullptr;
}

UEntity* UWorld::CreateEntity() {
    UEntity* NewEntity = new UEntity();
    Entities.push_back(NewEntity);
    return NewEntity;
}

UEntity* UWorld::GetFirstEntity() const {
    if (Entities.size() > 0)
        return Entities.front();

    return nullptr;
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
    for (auto Iter = Entities.begin(); Iter != Entities.end(); ++Iter){
        if (*Iter) {
            DestroyEntityImpl(*Iter);
            delete *Iter;
        }
    }
    Entities.clear();
}

void UWorld::DestroyEntityImpl(UEntity* Entity) {
    if (!Entity)
        return;

    Entity->DestroyImpl();
}
