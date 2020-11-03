#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <string>

class PlayerEntity : public Entity {
public:
    PlayerEntity();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
    virtual void update(float deltaTime) override;
private:
    void onEventHyperspace(const SDL_Event& event);
    void onEventShoot(const SDL_Event& event);
    
    const float acceleration = 7.5f;
    const float maxSpeed = 475.f;
    
    const std::string PLAYER_SHAPE = "playerShape";
    const std::string PLAYER_THRUST_SHAPE = "playerThrustShape";
    const std::string THRUST_SOUND = "thrustSound";
};
