#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <string>

class LivesEntity : public GameEntity {
public:
    LivesEntity();
        
    void addScore(int lives);
    void reset();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(const SDL_Event& event) override;
private:
    std::string toString() const;
    
    int lives = 0;
    
    const Eigen::Vector2f INITIAL_POSITION_SHAPE = Eigen::Vector2f(32, 12);
    const int MAX_LIVES = 99;
    const Eigen::Vector2f OFFSET_POSITION_SHAPE = Eigen::Vector2f(24, 0);
    const Eigen::Vector2f OFFSET_POSITION_TEXT = Eigen::Vector2f(-10, 0);
    const int PRECISION = 9;
};
