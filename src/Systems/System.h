#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components/Component.h"

#include <vector>

class Component;
class Entity;

class System {
public:
    virtual void Initialize(Entity* entity){}
    virtual void Update(double deltaTime, Entity* entity){}
    virtual void Finalize(Entity* entity){}

    virtual ~System() = default;
    
    const std::vector<EComponentClass>& GetComponentClasses() const {
        return requiredComponentClasses;
    }

protected:
    std::vector<EComponentClass> requiredComponentClasses{};
};

#endif
