#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class PlayerEntity : public Entity {
public:
    PlayerEntity() = default;
    virtual void render(SDL_Renderer& renderer) override;
private:
    SDL_Point points[4] = {
        {10, 10},
        {50, 10},
        {10, 50},
        {50, 50}
    };
};
