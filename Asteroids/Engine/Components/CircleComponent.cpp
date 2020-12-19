#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "SDL2_gfxPrimitives.h"

CircleComponent::CircleComponent(int radius) {
    this->radius = radius;
}

void CircleComponent::addVertex(const SDL_Point& point) {
}

void CircleComponent::render(SDL_Renderer& renderer) {
    if(getIsVisible()) {
        Eigen::Vector2f worldPosition = ownerEntity->getPosition();
        SDL_Point point;
        point.x = worldPosition.x();
        point.y = worldPosition.y();
        filledCircleRGBA(&renderer, point.x, point.y, radius , color.r, color.g, color.b, 255);
    }
}
