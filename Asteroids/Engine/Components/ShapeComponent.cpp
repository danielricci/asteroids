#include "Engine/Components/ShapeComponent.hpp"
#include "Engine/Components/TransformComponent.hpp"

ShapeComponent::ShapeComponent() {
    this->addNode(new TransformComponent());
}

ShapeComponent::ShapeComponent(std::initializer_list<SDL_Point> vertices) : ShapeComponent() {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

void ShapeComponent::addVertex(const SDL_Point& point) {
    this->vertices.push_back(point);
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
