#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "SDL2_gfxPrimitives.h"

CircleComponent::CircleComponent(const SDL_Point& point, int radius) {
    this->addVertex(point);
    this->radius = radius;
}

void CircleComponent::addVertex(const SDL_Point& point) {
    // Adding a vertex involves there being only ever a single vertex
    this->clear();
    ShapeComponent::addVertex(point);
}

void CircleComponent::render(SDL_Renderer& renderer) {
    if(!this->getNode<RenderComponent>()->isVisible) {
        return;
    }
    
    Eigen::Vector2f worldPosition = this->getWorldPosition();
    worldPosition.x() += (*this)[0].x;
    worldPosition.y() += (*this)[0].y;
    
    filledCircleRGBA(&renderer, worldPosition.x(), worldPosition.y(), this->radius , color.r, color.g, color.b, 255);
}
