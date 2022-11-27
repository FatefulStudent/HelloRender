#ifndef SIMPLE_COLLISION_COMPONENT_H
#define SIMPLE_COLLISION_COMPONENT_H

#include "Component.h"

#include <glm/vec3.hpp>

enum class ECollisionShape {
    Undefined,
    Circle,
    Rectangle,
};

class USimpleCollisionComponent : public UComponent {
public:
    USimpleCollisionComponent(ECollisionShape InCollisionShape,
                              float InCircleRadius);
    USimpleCollisionComponent(ECollisionShape InCollisionShape,
                              float InWidth,
                              float InHeight);
    virtual ~USimpleCollisionComponent() = default;

    float GetLeftBorderRelativeOffset() const;
    float GetRightBorderRelativeOffset() const;
    float GetUpBorderRelativeOffset() const;
    float GetBottomBorderRelativeOffset() const;

    ECollisionShape CollisionShape = ECollisionShape::Undefined;

    // Circle
    float CircleRadius = 1.0f;
    // ~Circle

    // Rectangle
    float Width = 1.0f;
    float Height = 1.0f;
    // ~Rectangle
};

#endif