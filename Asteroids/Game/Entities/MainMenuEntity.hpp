#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class MainMenuEntity : public Entity {
public:
    MainMenuEntity();
    virtual void render(SDL_Renderer& renderer) override;
};
