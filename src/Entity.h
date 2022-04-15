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

    void Destroy();

private:
    void DestroyImpl();
    friend class UWorld;
	// TODO: smartpointers
    std::vector<UComponent*> Components;
    int ID;
};

#endif

template <typename T, typename... Args>
inline void UEntity::AddComponent(Args... args) {
    auto NewObject = new T(std::forward<Args>(args)...);
    auto NewObjectAsComponent = static_cast<UComponent*>(NewObject);
    Components.push_back(NewObjectAsComponent);
}
