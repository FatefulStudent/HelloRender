#ifndef WORLD_H
#define WORLD_H

#include <vector>

class UEntity;
class USystem;

class UWorld 
{
public:
    static UWorld* CreateWorld();
    static void DestroyWorld();

    static UWorld* GetWorld();
    static UWorld* World;

    template<typename T>
    T* CreateSystem();

    USystem* GetFirstSystem() const;

    UEntity* CreateEntity();
    UEntity* GetFirstEntity() const;

    void DestroyEntity(UEntity* Entity);

private:
    void Destroy();
    void DestroyEntityImpl(UEntity* Entity);

    // TODO: move from raw pointers to new pointers
    std::vector<UEntity*> Entities;

    // TODO: move from raw pointers to new pointers
    std::vector<USystem*> Systems;
};


template <typename T>
inline T* UWorld::CreateSystem() {
    auto NewObject = new T();
    auto NewObjectAsSystem = static_cast<USystem*>(NewObject);
    Systems.push_back(NewObjectAsSystem);
    return NewObject;
}

#endif
