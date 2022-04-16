#ifndef SYSTEM_H
#define SYSTEM_H

class UComponent;
class UEntity;

class USystem {
public:
    virtual void Initialize(UEntity* Entity) = 0;
    virtual void Update(UEntity* Entity) = 0;
    virtual void Finalize(UEntity* Entity) = 0;
};

#endif
