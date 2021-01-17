#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <vector>

class ShapeComponent : public Component {
public:
    ShapeComponent() = default;
    ShapeComponent(std::initializer_list<SDL_Point> vertices);
    ShapeComponent(const std::vector<SDL_Point>& vertices);
    
    SDL_Point& operator[](int index);
    
    virtual void addVertex(const SDL_Point& point);
    void clear();
    unsigned long getSize() const;
    virtual void render(SDL_Renderer& renderer);
protected:
    std::vector<SDL_Point> vertices;
};
