#ifndef WORLD_H
#define WORLD_H

#include <vector>

class UEntity;

class UWorld 
{
public:
    static UWorld* CreateWorld();
    static void DestroyWorld();

    static UWorld* GetWorld();
    static UWorld* World;

    UEntity* CreateEntity();
    UEntity* GetFirstEntity() const;

    void DestroyEntity(UEntity* Entity);

private:
    void Destroy();
    void DestroyEntityImpl(UEntity* Entity);

    // TODO: move from raw pointers to new pointers
    std::vector<UEntity*> Entities;
};

#endif
