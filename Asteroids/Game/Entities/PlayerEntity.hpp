#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Shapes/Shape.hpp"
#include <SDL.h>

class PlayerEntity : public Entity {
public:
    PlayerEntity() = default;
    virtual void render(SDL_Renderer& renderer) override;
private:
    Shape shape {{10, 10}, {50, 10}, {10, 50}, {10, 10}};
};
