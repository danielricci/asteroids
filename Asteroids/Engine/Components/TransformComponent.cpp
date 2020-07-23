#include "Engine/Components/TransformComponent.hpp"

SDL_Rect TransformComponent::toRectangle() const {
    SDL_Rect rectangle;
    rectangle.x = positionVector.x();
    rectangle.y = positionVector.y();
    rectangle.w = dimensionVector.x();
    rectangle.h = dimensionVector.y();
    return rectangle;
}
