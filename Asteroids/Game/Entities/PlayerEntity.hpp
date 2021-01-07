#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class PlayerEntity : public GameEntity {
public:
    PlayerEntity();
    virtual SDL_Rect getEntityBounds() const override;
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
    virtual void update(float deltaTime) override;
private:
    void onEventHyperspace();
    void onEventShoot();
    
    const float ACCELERATION = 7.5f;
    const float MAX_SPEED = 475.f;
    
    const std::string PLAYER_SHIP = "playerShip";
    const std::string PLAYER_SHIP_EXHAUST = "playerShipExhaust";
};
