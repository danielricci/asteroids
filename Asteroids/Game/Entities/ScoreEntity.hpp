#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <string>

class ScoreEntity : public GameEntity {
public:
    void reset();
protected:
    ScoreEntity() = default;
    
    void addScore(int score);
    void setMaxScore(int maxScore);
    void setPrecision(int precision);
    
    virtual std::string toString() const;
private:
    int score = 0;
    
    int maxScore = 999999;
    int precision = 9;
};
