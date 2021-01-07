#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class MenuEntity : public Entity {
public:
    MenuEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
};
