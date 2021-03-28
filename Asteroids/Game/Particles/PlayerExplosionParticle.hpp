#pragma once

#include "Engine/Components/ShapeComponent.hpp"
#include "Game/Entities/GameEntity.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include <Eigen/Dense>
#include <vector>
#include "SDL.h"

class PlayerEntity;

class PlayerExplosionParticle : public GameEntity {
public:
    PlayerExplosionParticle(PlayerEntity* playerEntity);
    
    void play();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    bool isPlaying = false;
    const PlayerEntity* playerEntity;
    std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f>> edges;
};
