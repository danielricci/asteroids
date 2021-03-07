#pragma once

#include "Game/Entities/ScoreEntity.hpp"
#include <SDL.h>
#include <string>

class PlayerScoreEntity : public ScoreEntity {
public:
    PlayerScoreEntity();
    
    virtual void update(const SDL_Event& event) override;
};
