#include "Engine/Components/ShapeComponent.hpp"

ShapeComponent::ShapeComponent(const std::initializer_list<Eigen::Vector2f>& vertices) {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

ShapeComponent::ShapeComponent(const std::vector<Eigen::Vector2f>& vertices) {
    this->vertices = vertices;
}

Eigen::Vector2f& ShapeComponent::operator[](int index) {
    return vertices.at(index);
}

const Eigen::Vector2f& ShapeComponent::operator[](int index) const {
    return vertices.at(index);
}

void ShapeComponent::addVertex(const Eigen::Vector2f& vertex) {
    vertices.push_back(vertex);
}

void ShapeComponent::clear() {
    vertices.clear();
}

SDL_FRect ShapeComponent::getRectangle() const {
    float xMin = 0;
    float yMin = 0;
    float xMax = 0;
    float yMax = 0;

    for(const Eigen::Vector2f& vertex : vertices) {
        // TODO - validate this with the added this->position
        Eigen::Vector2f position = ownerEntity->getPosition(vertex, false) + this->position;
        xMin = std::min(xMin, position.x());
        yMin = std::min(yMin, position.y());
        xMax = std::max(xMax, position.x());
        yMax = std::max(yMax, position.y());
    }
    SDL_FRect rectangle;
    rectangle.x = xMin;
    rectangle.y = yMin;
    rectangle.w = xMax - xMin;
    rectangle.h = yMax - yMin;
    
    return rectangle;
}

unsigned long ShapeComponent::getSize() const {
    return vertices.size();
}

void ShapeComponent::render(SDL_Renderer& renderer) {
    if(!getIsVisible()) {
        return;
    }
    
    std::vector<SDL_FPoint> positions;
    for(const auto& vertex : vertices) {
        Eigen::Vector2f position = ownerEntity->getPosition(vertex) + this->position;
        positions.push_back({position.x(), position.y()});
    }
    SDL_RenderDrawLinesF(&renderer, &positions.front(), static_cast<int>(positions.size()));
}
