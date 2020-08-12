#pragma once

#include <vector>
#include "SDL.h"

class Shape {
public:
    Shape() = default;
    Shape(std::initializer_list<SDL_Point> vertices);
    void addVertex(const SDL_Point& point);
    void render(SDL_Renderer& renderer);
private:
    std::vector<SDL_Point> vertices;
};
