#ifndef COMPONENT_H
#define COMPONENT_H

enum class EComponentClass {
    Base,
    UModelComponent,
    UShaderComponent,
    UTransformComponent,
    UCameraComponent,
    UMovementComponent,
};

class UComponent {

public:
    UComponent();
    virtual ~UComponent();

    EComponentClass GetComponentClass() const { return ComponentClass; }

protected:
    EComponentClass ComponentClass = EComponentClass::Base;

private:
    long ID;
};

#endif