#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
enum class EComponentClass {
    Base,
    UModelComponent,
    UShaderComponent,
    UTransformComponent,
    UCameraComponent,
    UMovementComponent,
    USimpleCollisionComponent,
};

class UComponent {
public:
    explicit UComponent(const std::string& InComponentName);
    virtual ~UComponent();

    EComponentClass GetComponentClass() const { return ComponentClass; }

    const long ID;
    const std::string Name;

protected:
    EComponentClass ComponentClass = EComponentClass::Base;
};

#endif