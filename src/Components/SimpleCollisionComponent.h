#ifndef SIMPLE_COLLISION_COMPONENT_H
#define SIMPLE_COLLISION_COMPONENT_H

#include "Component.h"

#include <glm/vec3.hpp>

enum class ECollisionShape {
    Undefined,
    Circle,
    Rectangle,
};

class SimpleCollisionComponent : public Component {
public:
    SimpleCollisionComponent(ECollisionShape inCollisionShape,
        float inCircleRadius);
    SimpleCollisionComponent(ECollisionShape inCollisionShape,
        float inWidth,
        float inHeight);
    virtual ~SimpleCollisionComponent() = default;

    float GetLeftBorderRelativeOffset() const;
    float GetRightBorderRelativeOffset() const;
    float GetUpBorderRelativeOffset() const;
    float GetBottomBorderRelativeOffset() const;

    ECollisionShape collisionShape = ECollisionShape::Undefined;

    // Circle
    float circleRadius = 1.0f;
    // ~Circle

    // Rectangle
    float width = 1.0f;
    float height = 1.0f;
    // ~Rectangle
};

#endif