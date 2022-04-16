#include "Entity.h"
#include "Components/Component.h"
#include "World/World.h"

#include <iostream>

UEntity::UEntity() {
    static long GlobalID = 0;
    ID = GlobalID++;

    std::cout << "Entity #" << ID << " created!" << std::endl;
}

UEntity::~UEntity() {
    std::cout << "Entity #" << ID << " destroyed!" << std::endl;
}

void UEntity::Destroy() {
    auto World = UWorld::GetWorld();
    if (World)
        World->DestroyEntity(this);
}

void UEntity::DestroyImpl() {
    for (UComponent* Component : Components) {
        if (Component) {
            Component->Destroy();
            delete Component;
        }
    }

    Components.clear();
}
