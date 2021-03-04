#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class ScoreEntity : public GameEntity {
public:
    ScoreEntity();

    void reset();
    virtual void update(const SDL_Event& event) override;
protected:
    void addScore(int score);
    std::string toString() const;
private:
    int score = 0;
    
    const int MAX_SCORE = 999999;
    const int PRECISION = 9;
};
