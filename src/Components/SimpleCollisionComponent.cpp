#include "SimpleCollisionComponent.h"

USimpleCollisionComponent::USimpleCollisionComponent(
    ECollisionShape InCollisionShape,
    float InCircleRadius)
    : CollisionShape(InCollisionShape), CircleRadius(InCircleRadius) {
    assert(CollisionShape == ECollisionShape::Circle);
    ComponentClass = EComponentClass::USimpleCollisionComponent;
}

USimpleCollisionComponent::USimpleCollisionComponent(
    ECollisionShape InCollisionShape,
    float InWidth,
    float InHeight)
    : CollisionShape(InCollisionShape), Width(InWidth), Height(InHeight) {
    assert(CollisionShape == ECollisionShape::Rectangle);
    ComponentClass = EComponentClass::USimpleCollisionComponent;
}

float USimpleCollisionComponent::GetLeftBorderRelativeOffset() const {
    switch (CollisionShape) {
        case ECollisionShape::Circle:
            return -CircleRadius;
        case ECollisionShape::Rectangle:
            return -Width;
        default:
            assert(false);
    }
    return 0.0f;
}

float USimpleCollisionComponent::GetRightBorderRelativeOffset() const {
    switch (CollisionShape) {
        case ECollisionShape::Circle:
            return CircleRadius;
        case ECollisionShape::Rectangle:
            return Width;
        default:
            assert(false);
    }
    return 0.0f;
}

float USimpleCollisionComponent::GetUpBorderRelativeOffset() const {
    switch (CollisionShape) {
        case ECollisionShape::Circle:
            return CircleRadius;
        case ECollisionShape::Rectangle:
            return Height;
        default:
            assert(false);
    }
    return 0.0f;
}

float USimpleCollisionComponent::GetBottomBorderRelativeOffset() const {
    switch (CollisionShape) {
        case ECollisionShape::Circle:
            return -CircleRadius;
        case ECollisionShape::Rectangle:
            return -Height;
        default:
            assert(false);
    }
    return 0.0f;
}
