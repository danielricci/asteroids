#include "Engine/Shapes/Shape.hpp"

Shape::Shape(std::initializer_list<SDL_Point> vertices) {
    this->vertices.insert(this->vertices.cbegin(), vertices);
}

void Shape::addVertex(const SDL_Point& point) {
    this->vertices.push_back(point);
}

void Shape::render(SDL_Renderer& renderer) {
    SDL_RenderDrawLines(&renderer, &vertices.front(), static_cast<int>(vertices.size()));
}
