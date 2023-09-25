#include "Entity.h"
#include "Components/Component.h"
#include "World/World.h"

#include <iostream>
#include <utility>

static long GlobalID = 0;

Entity::Entity(const std::string& InEntityName)
    : id(GlobalID++),
      name(InEntityName + std::string("_") + std::to_string(id)) {
    std::cout << "Entity `" << name << "` created!" << std::endl;
}

Entity::~Entity() {
    std::cout << "Entity `" << name << "` destroyed!" << std::endl;
}

Component* Entity::GetComponentOfClass(
    EComponentClass ComponentClassEnum) const {
    auto Iter = componentClassToComponent.find(ComponentClassEnum);
    if (Iter != componentClassToComponent.end())
        return (*Iter).second;
    else
        return nullptr;
}

void Entity::Destroy() {
    auto World = World::GetWorld();
    if (World)
        World->DestroyEntity(this);
}

void Entity::DestroyImpl() {
    for (Component* Component : components) {
        delete Component;
    }

    components.clear();
    componentClassToComponent.clear();
}
