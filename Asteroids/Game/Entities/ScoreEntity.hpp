#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
#include <string>

class ScoreEntity : public GameEntity {
public:
    void reset();
protected:
    ScoreEntity() = default;
    
    void addScore(int score);
    virtual std::string toString() const;
private:
    int score = 0;
    
    const int MAX_SCORE = 999999;
    const int PRECISION = 9;
};
