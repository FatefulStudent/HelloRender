#ifndef ENTITY_H
#define ENTITY_H

#include "Components/Component.h"

#include <string>
#include <unordered_map>
#include <vector>

class Component;

class Entity {
public:
    explicit Entity(const std::string& InEntityName);
    ~Entity();

    template <typename T, typename... Args>
    void AddComponent(Args... args);

    template <typename T>
    T* GetComponentOfClass() const;

    Component* GetComponentOfClass(EComponentClass ComponentClassEnum) const;

    void Destroy();

    const int id;
    const std::string name;

private:
    void DestroyImpl();
    friend class World;

    std::unordered_map<EComponentClass, Component*> componentClassToComponent;

    // TODO: smartpointers
    std::vector<Component*> components;
};

template <typename T, typename... Args>
inline void Entity::AddComponent(Args... args) {
    auto newObject = new T(std::forward<Args>(args)...);
    auto newObjectAsComponent = static_cast<Component*>(newObject);
    components.push_back(newObjectAsComponent);
    componentClassToComponent.emplace(
        newObjectAsComponent->GetComponentClass(), newObjectAsComponent);
}

template <typename T>
inline T* Entity::GetComponentOfClass() const {
    for (Component* component : components) {
        T* componentCasted = dynamic_cast<T*>(component);
        if (componentCasted)
            return componentCasted;
    }
    return nullptr;
}

#endif
