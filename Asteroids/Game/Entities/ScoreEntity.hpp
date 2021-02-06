#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
private:
};
