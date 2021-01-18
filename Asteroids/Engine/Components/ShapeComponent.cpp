#include "Engine/Components/RenderComponent.hpp"
#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

ShapeComponent::ShapeComponent(std::initializer_list<Eigen::Vector2f> vertices) {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

Eigen::Vector2f& ShapeComponent::operator[](int index) {
    return this->vertices.at(index);
}

void ShapeComponent::addVertex(const Eigen::Vector2f& vertex) {
    this->vertices.push_back(vertex);
}

void ShapeComponent::clear() {
    this->vertices.clear();
}

unsigned long ShapeComponent::getSize() const {
    return this->vertices.size();
}

void ShapeComponent::normalize(const Eigen::Vector2f& vector) {
    for(auto& vertex : this->vertices) {
        vertex.x() += vector.x();
        vertex.y() += vector.y();
    }
}

void ShapeComponent::render(SDL_Renderer& renderer) {
    std::vector<SDL_FPoint> positions;
    for(const auto& vertex : this->vertices) {
        Eigen::Vector2f position = this->ownerEntity->getPosition(vertex);
        positions.push_back({position.x(), position.y()});
    }
    SDL_RenderDrawLinesF(&renderer, &positions.front(), static_cast<int>(positions.size()));
}
