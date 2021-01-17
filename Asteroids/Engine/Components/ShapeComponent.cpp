#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <algorithm>
#include <cmath>

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

void ShapeComponent::render(SDL_Renderer& renderer) {
    std::vector<SDL_Point> finalPositions;
    for(const SDL_Point& vertex : this->vertices) {
        Eigen::Vector2f position = this->ownerEntity->getPosition({vertex.x, vertex.y});
        SDL_Point point;
        point.x = position.x();
        point.y = position.y();
        finalPositions.push_back(point);
    }
    SDL_RenderDrawLines(&renderer, &finalPositions.front(), static_cast<int>(finalPositions.size()));
}

void ShapeComponent::clear() {
    this->vertices.clear();
}
