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

    UEntity* CreateEntity() const;
    UEntity* GetFirstEntity() const;

private:
    void Destroy();

    // TODO: move from raw pointers to new pointers
    std::vector<UEntity*> Entities;
};

#endif
