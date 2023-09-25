#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
enum class EComponentClass {
    base,
    modelComponent,
    shaderComponent,
    transformComponent,
    cameraComponent,
    movementComponent,
    simpleCollisionComponent,
};

class Component {
public:
    explicit Component(const std::string& InComponentName);
    virtual ~Component();

    EComponentClass GetComponentClass() const { return componentClass; }

    const long id;
    const std::string name;

protected:
    EComponentClass componentClass = EComponentClass::base;
};

#endif