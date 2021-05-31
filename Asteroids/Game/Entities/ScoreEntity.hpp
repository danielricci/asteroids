#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <string>

class ScoreEntity : public GameEntity {
public:
    int getScore() const;
    virtual void reset();
    void setScore(int score);
    
protected:
    ScoreEntity() = default;
    
    void addScore(int score);
    void setMaxScore(int maxScore);
    void setPrecision(int precision);
    virtual std::string toString() const;
private:
    const Eigen::Vector2f OFFSET_POSITION_TEXT = Eigen::Vector2f(-20, 0);

    int maxScore = 999999;
    int precision = 2;
    int score = 0;
};
