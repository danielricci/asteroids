#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <vector>

class ShapeComponent : public Component {
public:
    ShapeComponent();
    ShapeComponent(std::initializer_list<SDL_Point> vertices);
    
    SDL_Point getShapeCenter() const;
    
    SDL_Point& operator[](int index);
    unsigned long getSize() const;
    void clear();
    
    virtual void addVertex(const SDL_Point& point);
    virtual void render(SDL_Renderer& renderer);
private:
    std::vector<SDL_Point> vertices;
};
