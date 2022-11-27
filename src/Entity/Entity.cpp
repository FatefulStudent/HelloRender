#include "Entity.h"
#include "Components/Component.h"
#include "World/World.h"

#include <iostream>
#include <utility>

static long GlobalID = 0;

UEntity::UEntity(const std::string& InEntityName)
    : ID(GlobalID++),
      Name(InEntityName + std::string("_") + std::to_string(ID)) {
    std::cout << "Entity `" << Name << "` created!" << std::endl;
}

UEntity::~UEntity() {
    std::cout << "Entity `" << Name << "` destroyed!" << std::endl;
}

UComponent* UEntity::GetComponentOfClass(
    EComponentClass ComponentClassEnum) const {
    auto Iter = ComponentClassToComponent.find(ComponentClassEnum);
    if (Iter != ComponentClassToComponent.end())
        return (*Iter).second;
    else
        return nullptr;
}

void UEntity::Destroy() {
    auto World = UWorld::GetWorld();
    if (World)
        World->DestroyEntity(this);
}

void UEntity::DestroyImpl() {
    for (UComponent* Component : Components) {
        delete Component;
    }

    Components.clear();
    ComponentClassToComponent.clear();
}
