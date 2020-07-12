#include "Engine/Components/TransformComponent.hpp"

SDL_Rect TransformComponent::getRectangle() const {
    SDL_Rect rectangle;
    rectangle.x = positionVector.x();
    rectangle.y = positionVector.y();
    rectangle.w = dimensionVector.x();
    rectangle.h = dimensionVector.y();
    return rectangle;
}

Eigen::Vector2f TransformComponent::getWorldPosition() const {
    // TODO: TransformComponent::getWorldPosition() const
    return Eigen::Vector2f();
}
