#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "SDL2_gfxPrimitives.h"

CircleComponent::CircleComponent(int radius) {
    this->radius = radius;
}

void CircleComponent::addVertex(const Eigen::Vector2f& vertex) {
}

void CircleComponent::render(SDL_Renderer& renderer) {
    Eigen::Vector2f position = ownerEntity->getPosition();
    filledCircleRGBA(&renderer, position.x(), position.y(), radius , color.r, color.g, color.b, 255);
}
