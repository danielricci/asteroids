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

ShapeComponent::ShapeComponent(const std::vector<SDL_Point>& vertices) : ShapeComponent() {
    this->vertices = vertices;
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
    if(vertices.size() == 0) {
        return SDL_Point { 0, 0 };
    }
    else if(vertices.size() == 1) {
        return vertices[0];
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
    std::vector<SDL_Point> finalPositions;
    for(const SDL_Point& vertex : this->vertices) {
        finalPositions.push_back(this->getVertexPosition(vertex));
    }
    SDL_RenderDrawLines(&renderer, &finalPositions.front(), static_cast<int>(finalPositions.size()));
}

void ShapeComponent::clear() {
    this->vertices.clear();
}

SDL_Point ShapeComponent::getVertexPosition(SDL_Point vertex) {
    float orientation = TransformComponent::toRadians(this->getWorldOrientation());
    
    double cosResult = std::cos(orientation);
    double sinResult = std::sin(orientation);
    double expr1 = (cosResult * vertex.x) - (sinResult * vertex.y);
    double expr2 = (sinResult * vertex.x) + (cosResult * vertex.y);
    vertex.x = expr1;
    vertex.y = expr2;
    
    Eigen::Vector2f worldPosition = this->getWorldPosition();
    vertex.x += static_cast<int>(worldPosition.x());
    vertex.y += static_cast<int>(worldPosition.y());
    
    return vertex;
}
