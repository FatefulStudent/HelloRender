#include "World.h"
#include "Entity/Entity.h"
#include "Systems/System.h"

#include <algorithm>

World* World::world = nullptr;
Entity* World::localPlayer = nullptr;

World* World::CreateWorld() {
    world = new World();
    return world;
}

void World::DestroyWorld() {
    if (world) {
        world->Destroy();

        delete world;
        world = nullptr;
    }
}

World* World::GetWorld() {
    return world;
}

std::vector<Entity*> World::GetAllEntitiesWithComponents(
    const std::vector<EComponentClass>& requiredComponentClasses) const {
    std::vector<Entity*> Result{};

    for (Entity* entity : entities) {
        if (entity) {
            const std::unordered_map<EComponentClass, Component*>&
                classesToComponents = entity->componentClassToComponent;

            bool bHasAllClasses = true;
            for (EComponentClass ComponentClass : requiredComponentClasses) {
                const bool bContains =
                    classesToComponents.find(ComponentClass) !=
                    classesToComponents.end();

                if (!bContains) {
                    bHasAllClasses = false;
                    break;
                }
            }

            if (bHasAllClasses)
                Result.push_back(entity);
        }
    }
    return Result;
}

void World::Initialize() const {
    for (System* System : systems) {
        InitializeSystem(System);
    }
}

void World::InitializeSystem(System* System) const {
    if (!System)
        return;
    const std::vector<Entity*> ValidEntities =
        GetAllEntitiesWithComponents(System->GetComponentClasses());

    for (Entity* Entity : ValidEntities) {
        System->Initialize(Entity);
    }
}

void World::Update(double deltaTime) const{
    for (System* System : systems) {
        UpdateSystem(deltaTime, System);
    }
}

void World::UpdateSystem(double deltaTime, System* system) const {
    if (!system)
        return;

    const std::vector<Entity*> validEntities =
        GetAllEntitiesWithComponents(system->GetComponentClasses());

    for (Entity* entity : validEntities) {
        system->Update(deltaTime, entity);
    }
}

void World::Finalize() const {
    for (System* system : systems) {
        FinalizeSystem(system);
    }
}

void World::FinalizeSystem(System* system) const {
    if (!system)
        return;
    const std::vector<Entity*> validEntities =
        GetAllEntitiesWithComponents(system->GetComponentClasses());

    for (Entity* entity : validEntities) {
        system->Finalize(entity);
    }
}


Entity* World::CreateEntity(const std::string& inEntityName) {
    auto* newEntity = new Entity(inEntityName);
    entities.push_back(newEntity);
    return newEntity;
}

void World::DestroyEntity(Entity* entity) {
    if (!entity)
        return;

    DestroyEntityImpl(entity);

    auto entityIter = std::find(entities.begin(), entities.end(), entity);
    if (entityIter != entities.end())
        entities.erase(entityIter);
    delete entity;
}

void World::Destroy() {
    for (Entity* entity : entities) {
        if (entity) {
            DestroyEntityImpl(entity);
            delete entity;
        }
    }
    entities.clear();

    for (System* system : systems) {
        delete system;
    }
    systems.clear();
}

void World::DestroyEntityImpl(Entity* entity) {
    if (!entity)
        return;

    entity->DestroyImpl();
}
