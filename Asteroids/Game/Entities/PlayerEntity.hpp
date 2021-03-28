#pragma once

#include "Game/Entities/GameEntity.hpp"
#include "Game/Particles/PlayerExplosionParticle.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class PlayerExplosionParticle;

class PlayerEntity : public GameEntity {
public:
    PlayerEntity();
    virtual ~PlayerEntity();
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void render(SDL_Renderer& renderer) override;
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
    
    PlayerExplosionParticle* particle = nullptr;
};
