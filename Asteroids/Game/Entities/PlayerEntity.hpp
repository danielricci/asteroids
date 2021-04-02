#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class PlayerEntity : public GameEntity {
public:
    PlayerEntity();
    virtual ~PlayerEntity() = default;
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void update(const SDL_Event& event) override;
    virtual void update(float deltaTime) override;
    
    inline static const std::string PLAYER_SHIP = "playerShip";
    inline static const std::string PLAYER_SHIP_EXHAUST = "playerShipExhaust";
private:
    void onEventHyperspace();
    void onEventShoot();
    void onEventThrust(bool isThrustActivated);
    
    const float ACCELERATION = 7.5f;
    const float MAX_SPEED = 475.f;
};
