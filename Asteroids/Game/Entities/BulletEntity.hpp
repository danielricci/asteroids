#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class BulletEntity : public Entity {
public:
    BulletEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
private:
    const int speed = 700;
    
    float timeTravelled = 0;
    static const int MAX_DISTANCE = 675;
};
