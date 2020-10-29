#include "Engine/Components/CircleComponent.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
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
    std::vector<SDL_Point> finalPosition(this->vertices);
    
    float orientation = TransformComponent::toRadians(this->getWorldOrientation());
    for(SDL_Point& vertex : finalPosition) {
        double cosResult = std::cos(orientation);
        double sinResult = std::sin(orientation);
        double expr1 = (cosResult * vertex.x) - (sinResult * vertex.y);
        double expr2 = (sinResult * vertex.x) + (cosResult * vertex.y);
        vertex.x = expr1;
        vertex.y = expr2;
    }

    Eigen::Vector2f worldPosition = this->getWorldPosition();
    for(SDL_Point& vertex : finalPosition) {
        vertex.x += static_cast<int>(worldPosition.x());
        vertex.y += static_cast<int>(worldPosition.y());
    }
    
    filledCircleRGBA(&renderer, worldPosition.x(), worldPosition.y(), this->radius , color.r, color.g, color.b, 255);
}
