#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components/Component.h"

#include <vector>

class UComponent;
class UEntity;

class USystem {
public:
    virtual void Initialize(UEntity* Entity){};
    virtual void Update(float DeltaTime, UEntity* Entity){};
    virtual void Finalize(UEntity* Entity){};

    const std::vector<EComponentClass>& GetComponentClasses() const {
        return RequiredComponentClasses;
    };

protected:
    std::vector<EComponentClass> RequiredComponentClasses{};
};

#endif
