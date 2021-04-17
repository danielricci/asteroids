#pragma once

#include "Game/Entities/GameEntity.hpp"
#include "SDL.h"

class GameOverEntity : public GameEntity {
public:
    GameOverEntity();
    
    virtual void update(const SDL_Event& event) override;
private:
    bool isGameOver = false;
};
