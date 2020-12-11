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
    const int speed = 925;
    
    float timeTravelled = 0;
    static const int MAX_DISTANCE = 875;
};
