#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <algorithm>
#include <cmath>

ShapeComponent::ShapeComponent(std::initializer_list<Eigen::Vector2f> vertices) {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

void ShapeComponent::addVertex(const Eigen::Vector2f& vertex) {
    this->vertices.push_back(vertex);
}

Eigen::Vector2f& ShapeComponent::operator[](int index) {
    return this->vertices.at(index);
}

unsigned long ShapeComponent::getSize() const {
    return this->vertices.size();
}

void ShapeComponent::render(SDL_Renderer& renderer) {
    std::vector<SDL_FPoint> positions;
    for(const auto& vertex : this->vertices) {
        Eigen::Vector2f position = this->ownerEntity->getPosition(vertex);
        positions.push_back({position.x(), position.y()});
    }
    SDL_RenderDrawLinesF(&renderer, &positions.front(), static_cast<int>(positions.size()));
}

void ShapeComponent::clear() {
    this->vertices.clear();
}
