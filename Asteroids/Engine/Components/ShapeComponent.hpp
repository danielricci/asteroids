#pragma once

#include "Engine/Components/Component.hpp"
#include <vector>
#include "SDL.h"

class ShapeComponent : public Component {
public:
    ShapeComponent();
    ShapeComponent(std::initializer_list<SDL_Point> vertices);
    
    SDL_Point& operator[](int index);
    unsigned long getSize() const;
    
    void addVertex(const SDL_Point& point);
    void render(SDL_Renderer& renderer);
private:
    SDL_Point getShapeCenter() const;
    std::vector<SDL_Point> vertices;
};
