#ifndef ENTITY_H
#define ENTITY_H

#include "Components/Component.h"

#include <string>
#include <unordered_map>
#include <vector>

class UComponent;

class UEntity {
public:
    explicit UEntity(const std::string& InEntityName);
    ~UEntity();

    template <typename T, typename... Args>
    void AddComponent(Args... args);

    template <typename T>
    T* GetComponentOfClass() const;

    UComponent* GetComponentOfClass(EComponentClass ComponentClassEnum) const;

    void Destroy();

    const int ID;
    const std::string Name;

private:
    void DestroyImpl();
    friend class UWorld;

    std::unordered_map<EComponentClass, UComponent*> ComponentClassToComponent;

    // TODO: smartpointers
    std::vector<UComponent*> Components;
};

template <typename T, typename... Args>
inline void UEntity::AddComponent(Args... args) {
    auto NewObject = new T(std::forward<Args>(args)...);
    auto NewObjectAsComponent = static_cast<UComponent*>(NewObject);
    Components.push_back(NewObjectAsComponent);
    ComponentClassToComponent.emplace(
        NewObjectAsComponent->GetComponentClass(), NewObjectAsComponent);
}

template <typename T>
inline T* UEntity::GetComponentOfClass() const {
    for (UComponent* Component : Components) {
        T* ComponentCasted = dynamic_cast<T*>(Component);
        if (ComponentCasted)
            return ComponentCasted;
    }
    return nullptr;
}

#endif
