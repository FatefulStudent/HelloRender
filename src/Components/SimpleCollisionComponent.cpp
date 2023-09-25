#include "SimpleCollisionComponent.h"

SimpleCollisionComponent::SimpleCollisionComponent(
    ECollisionShape inCollisionShape,
    float inCircleRadius)
    : Component(std::string("SimpleCollisionComponent")),
      collisionShape(inCollisionShape),
      circleRadius(inCircleRadius) {
    assert(collisionShape == ECollisionShape::Circle);
    componentClass = EComponentClass::simpleCollisionComponent;
}

SimpleCollisionComponent::SimpleCollisionComponent(
    ECollisionShape inCollisionShape,
    float inWidth,
    float inHeight)
    : Component(std::string("SimpleCollisionComponent")),
      collisionShape(inCollisionShape),
      width(inWidth),
      height(inHeight) {
    assert(collisionShape == ECollisionShape::Rectangle);
    componentClass = EComponentClass::simpleCollisionComponent;
}

float SimpleCollisionComponent::GetLeftBorderRelativeOffset() const {
    switch (collisionShape) {
        case ECollisionShape::Circle:
            return -circleRadius;
        case ECollisionShape::Rectangle:
            return -width;
        default:
            assert(false);
    }
    return 0.0f;
}

float SimpleCollisionComponent::GetRightBorderRelativeOffset() const {
    switch (collisionShape) {
        case ECollisionShape::Circle:
            return circleRadius;
        case ECollisionShape::Rectangle:
            return width;
        default:
            assert(false);
    }
    return 0.0f;
}

float SimpleCollisionComponent::GetUpBorderRelativeOffset() const {
    switch (collisionShape) {
        case ECollisionShape::Circle:
            return circleRadius;
        case ECollisionShape::Rectangle:
            return height;
        default:
            assert(false);
    }
    return 0.0f;
}

float SimpleCollisionComponent::GetBottomBorderRelativeOffset() const {
    switch (collisionShape) {
        case ECollisionShape::Circle:
            return -circleRadius;
        case ECollisionShape::Rectangle:
            return -height;
        default:
            assert(false);
    }
    return 0.0f;
}
