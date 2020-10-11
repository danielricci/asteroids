#pragma once

#include "Engine/Components/ShapeComponent.hpp"
#include <SDL.h>

class CircleComponent : public ShapeComponent {
public:
    CircleComponent(const SDL_Point& point, int radius);
    
    virtual void addVertex(const SDL_Point& point) override;
    virtual void render(SDL_Renderer& renderer) override;
private:
    int radius = 0;
    SDL_Color color { 255, 255, 255 };
};
