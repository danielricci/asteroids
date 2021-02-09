#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();
    void reset();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
private:
    void addScore(int score);
    std::string toString() const;

    int score = 0;
    const int MAX_SCORE = 99990;
    const int PRECISION = 5;
};
