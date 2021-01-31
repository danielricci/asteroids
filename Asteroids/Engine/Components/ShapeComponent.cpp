#include "Engine/Components/ShapeComponent.hpp"

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

SDL_Rect ShapeComponent::getRectangle() const {
    float xMin = 0;
    float yMin = 0;
    float xMax = 0;
    float yMax = 0;

    for(const auto& vertex : vertices) {
        xMin = std::min(xMin, vertex.x());
        yMin = std::min(yMin, vertex.y());
        xMax = std::max(xMax, vertex.x());
        yMax = std::max(yMax, vertex.y());
    }
    
    SDL_Rect rectangle;
    rectangle.x = xMin;
    rectangle.y = yMin;
    rectangle.w = xMax - xMin;
    rectangle.h = yMax - yMin;
    
    return rectangle;
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
