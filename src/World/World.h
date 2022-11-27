#ifndef WORLD_H
#define WORLD_H

#include "Components/Component.h"

#include <vector>


class UEntity;
class USystem;

class UWorld 
{
public:
    static UWorld* CreateWorld();
    static void DestroyWorld();

    static UWorld* GetWorld();
    static UWorld* World;

    static UEntity* LocalPlayer;

    std::vector<UEntity*> GetAllEntitiesWithComponents(
        const std::vector<EComponentClass>& RequiredComponentClasses) const;

    template<typename T>
    T* CreateSystem();

    void Initialize() const;
    void InitializeSystem(USystem* System) const;

    void Update(float DeltaTime) const;
    void UpdateSystem(float DeltaTime, USystem* System) const;

    void Finalize() const;
    void FinalizeSystem(USystem* System) const;

    UEntity* CreateEntity(const std::string& InEntityName);

    void DestroyEntity(UEntity* Entity);

private:
    void Destroy();
    void DestroyEntityImpl(UEntity* Entity);

    // TODO: move from raw pointers to new pointers
    std::vector<UEntity*> Entities;

    // TODO: move from raw pointers to new pointers
    std::vector<USystem*> Systems;
};


template <typename T>
inline T* UWorld::CreateSystem() {
    auto NewObject = new T();
    auto NewObjectAsSystem = static_cast<USystem*>(NewObject);
    Systems.push_back(NewObjectAsSystem);
    return NewObject;
}

#endif
