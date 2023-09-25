#ifndef WORLD_H
#define WORLD_H

#include "Components/Component.h"

#include <vector>


class Entity;
class System;

class World 
{
public:
    static World* CreateWorld();
    static void DestroyWorld();

    static World* GetWorld();
    static World* world;

    static Entity* localPlayer;

    std::vector<Entity*> GetAllEntitiesWithComponents(
        const std::vector<EComponentClass>& requiredComponentClasses) const;

    template<typename T>
    T* CreateSystem();

    void Initialize() const;
    void InitializeSystem(System* System) const;

    void Update(double deltaTime) const;
    void UpdateSystem(double deltaTime, System* system) const;

    void Finalize() const;
    void FinalizeSystem(System* system) const;

    Entity* CreateEntity(const std::string& inEntityName);

    void DestroyEntity(Entity* entity);

private:
    void Destroy();
    void DestroyEntityImpl(Entity* entity);

    // TODO: move from raw pointers to new pointers
    std::vector<Entity*> entities;

    // TODO: move from raw pointers to new pointers
    std::vector<System*> systems;
};


template <typename T>
inline T* World::CreateSystem() {
    auto newObject = new T();
    auto newObjectAsSystem = static_cast<System*>(newObject);
    systems.push_back(newObjectAsSystem);
    return newObject;
}

#endif
