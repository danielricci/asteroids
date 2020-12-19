#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <vector>

class ShapeComponent : public Component {
public:
    ShapeComponent() = default;
    ShapeComponent(std::initializer_list<SDL_Point> vertices);
    ShapeComponent(const std::vector<SDL_Point>& vertices);
    
    SDL_Point getShapeCenter() const;
    
    SDL_Point& operator[](int index);
    unsigned long getSize() const;
    void clear();
    
    virtual void addVertex(const SDL_Point& point);
    virtual void render(SDL_Renderer& renderer);
    SDL_Point getVertexPosition(SDL_Point vertex);
    
protected:
    std::vector<SDL_Point> vertices;
};
