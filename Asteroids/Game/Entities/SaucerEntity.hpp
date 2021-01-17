#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <SDL.h>

class SaucerEntity : public GameEntity {
public:
    SaucerEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    int speed = 65;
};
