#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class PlayerEntity : public Entity {
public:
    PlayerEntity();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
    virtual void update(float deltaTime) override;
};
