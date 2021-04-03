#pragma once

#include "Game/Entities/GameEntity.hpp"
#include "Game/ManagerHelper.hpp"
#include <Eigen/Dense>
#include "Engine/System/Event.hpp"
#include "Engine/System/EventArgs.hpp"
#include <vector>
#include "SDL.h"

class EnemyExplosionParticle : public GameEntity {
public:
    EnemyExplosionParticle();
    
    void play();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    
    Event<EventArgs> eventOnStop;
private:
    const float DURATION = .8;
    const int SPEED = 60;
    
    std::vector<Eigen::Vector2f> points;
    float elapsedTime = 0.f;
    bool isPlaying = false;
};
