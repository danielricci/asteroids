#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();
    void addScore(int score);
    void reset();
    virtual void render(SDL_Renderer& renderer) override;
    std::string toString() const;
private:
    int score = 0;
    const int precision = 6;
};
