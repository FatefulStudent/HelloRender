#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components/Component.h"

#include <vector>

class UComponent;
class UEntity;

class USystem {
public:
    virtual void Initialize(UEntity* Entity) = 0;
    virtual void Update(UEntity* Entity) = 0;
    virtual void Finalize(UEntity* Entity) = 0;

    const std::vector<EComponentClass>& GetComponentClasses() const {
        return RequiredComponentClasses;
    };

protected:
    std::vector<EComponentClass> RequiredComponentClasses{};
};

#endif
