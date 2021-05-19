#pragma once

#include "Game/Entities/GameEntity.hpp"
#include "Game/Managers/ManagerHelper.hpp"
#include <Eigen/Dense>
#include "Engine/System/Event.hpp"
#include "Engine/System/EventArgs.hpp"
#include <vector>
#include "SDL.h"

class PlayerExplosionParticle : public GameEntity {
public:
    PlayerExplosionParticle();
    
    void play();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    
    Event<EventArgs> eventOnStop;
private:
    const int DURATION = 2.2;
    const int SPEED = 14;
    
    std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f>> edges;
    float elapsedTime = 0.f;
    bool isPlaying = false;
};
