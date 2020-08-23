#include "Engine/Components/TransformComponent.hpp"

SDL_Rect TransformComponent::toRectangle() const {
    SDL_Rect rectangle;
    rectangle.x = position.x();
    rectangle.y = position.y();
    rectangle.w = dimension.x();
    rectangle.h = dimension.y();
    return rectangle;
}
