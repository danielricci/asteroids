#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class BulletEntity : public Entity {
public:
    BulletEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
};