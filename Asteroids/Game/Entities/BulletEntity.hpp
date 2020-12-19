#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <SDL.h>

class BulletEntity : public GameEntity {
public:
    BulletEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    const int SPEED = 925;
    const int MAX_DISTANCE = 600;

    float timeTravelled = 0;
};
