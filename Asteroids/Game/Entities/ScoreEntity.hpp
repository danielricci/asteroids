#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();
    void addScore(int score);
    void addScoreAsteroidHit();
    void reset();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    std::string toString() const;
private:
    int score = 0;
    const int precision = 6;
    bool isDirty = true;
};
