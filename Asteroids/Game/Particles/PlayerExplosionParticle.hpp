#pragma once

#include "Game/Entities/GameEntity.hpp"
#include "Game/ManagerHelper.hpp"
#include <Eigen/Dense>
#include "Engine/System/Event.hpp"
#include "Engine/System/EventArgs.hpp"
#include <vector>
#include "SDL.h"

class PlayerEntity;

class PlayerExplosionParticle : public GameEntity {
public:
    PlayerExplosionParticle();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    
    Event<EventArgs> eventOnStop;
private:
    const int DURATION = 2.2;
    const int SPEED = 14;
    
    std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f>> edges;
    float elapsedTime = 0.f;
    bool isPlaying = false;
};
