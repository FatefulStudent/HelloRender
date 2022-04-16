#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class UComponent;

class UEntity {
public:
    UEntity();
    ~UEntity();

    template<typename T, typename ... Args>
    void AddComponent(Args... args);

    template<typename T>
    T* GetComponentOfClass() const;

    void Destroy();

private:
    void DestroyImpl();
    friend class UWorld;
	// TODO: smartpointers
    std::vector<UComponent*> Components;
    int ID;
};

template <typename T, typename... Args>
inline void UEntity::AddComponent(Args... args) {
    auto NewObject = new T(std::forward<Args>(args)...);
    auto NewObjectAsComponent = static_cast<UComponent*>(NewObject);
    Components.push_back(NewObjectAsComponent);
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
