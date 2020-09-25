#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <algorithm>
#include <cmath>

ShapeComponent::ShapeComponent() {
    this->addNode(new TransformComponent());
    this->addNode(new RenderComponent());
}

ShapeComponent::ShapeComponent(std::initializer_list<SDL_Point> vertices) : ShapeComponent() {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

void ShapeComponent::addVertex(const SDL_Point& point) {
    this->vertices.push_back(point);
}

SDL_Point& ShapeComponent::operator[](int index) {
    return this->vertices.at(index);
}

unsigned long ShapeComponent::getSize() const {
    return this->vertices.size();
}

SDL_Point ShapeComponent::getShapeCenter() const {
    if(vertices.size() < 2) {
        return SDL_Point({0, 0});
    }
    
    int xMin = INT_MAX;
    int yMin = INT_MAX;
    
    int xMax = INT_MIN;
    int yMax = INT_MIN;
    
    for(const SDL_Point& point : vertices) {
        xMin = std::min(xMin, point.x);
        yMin = std::min(yMin, point.y);
        xMax = std::max(xMax, point.x);
        yMax = std::max(yMax, point.y);
    }
    
    return SDL_Point({(xMax - xMin)/2, (yMax - yMin)/2});
}

void ShapeComponent::render(SDL_Renderer& renderer) {
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

    SDL_RenderDrawLines(&renderer, &finalPosition.front(), static_cast<int>(finalPosition.size()));
}
