#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include <algorithm>

ShapeComponent::ShapeComponent() {
    this->addNode(new TransformComponent());
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
    if(vertices.size() == 0) {
        return SDL_Point({0, 0});
    }
    else if(vertices.size() == 1) {
        return vertices.at(0);
    }
    
    int xMax = 0;
    int yMax = 0;
    for(const SDL_Point& point : vertices) {
        xMax = std::max(xMax, point.x);
        yMax = std::max(yMax, point.y);
    }
    
    return SDL_Point({xMax/2, yMax/2});
}

void ShapeComponent::render(SDL_Renderer& renderer) {    
    Eigen::Vector2f worldPosition = this->getWorldPosition();
    std::vector<SDL_Point> updatedPositions;
    for(auto& vertex : this->vertices) {
        SDL_Point point {
            vertex.x + static_cast<int>(worldPosition.x()),
            vertex.y + static_cast<int>(worldPosition.y())
        };
        updatedPositions.push_back(point);
    }
    SDL_RenderDrawLines(&renderer, &updatedPositions.front(), static_cast<int>(updatedPositions.size()));
}
