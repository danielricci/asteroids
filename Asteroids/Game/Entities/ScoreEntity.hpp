#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();
    void addScore(int score);
    void reset();
    virtual void render(SDL_Renderer& renderer) override;
private:
    int score = 0;
};
