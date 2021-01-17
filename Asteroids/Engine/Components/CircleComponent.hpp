#pragma once

#include "Engine/Components/ShapeComponent.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class CircleComponent : public ShapeComponent {
public:
    CircleComponent(int radius);
    virtual void addVertex(const Eigen::Vector2f& vertex) override;
    virtual void render(SDL_Renderer& renderer) override;
private:
    int radius = 0;
    const SDL_Color color { 255, 255, 255 };
};
