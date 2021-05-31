#pragma once

#include "Game/Entities/ScoreEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class PlayerScoreEntity : public ScoreEntity {
public:
    PlayerScoreEntity(const Eigen::Vector2f& position);
    
    virtual void reset() override;
    virtual void update(const SDL_Event& event) override;
private:
    const Eigen::Vector2f initialPosition;
};
