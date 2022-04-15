#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "System.h"

class UEntity;
class UComponent;


class URenderSystem : public USystem {
public:
    virtual void Initialize(UEntity* Entity);
    virtual void Update(UEntity* Entity);
    virtual void Finalize(UEntity* Entity);
};

#endif
