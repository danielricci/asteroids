#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <queue>

class SaucerEntity : public GameEntity {
public:
    enum class SaucerType {
        SAUCER_SMALL = 1,
        SAUCER_LARGE = 2
    };
    
    SaucerEntity(SaucerType saucerType);
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void update(float deltaTime) override;
    
    const SaucerType saucerType;
private:
    int speed = 1;
    std::queue<Eigen::Vector2f> pathfinding {{
        Eigen::Vector2f(800, 200),
        //Eigen::Vector2f(600, 500),
        //Eigen::Vector2f(300, 900),
        //Eigen::Vector2f(1200, 900),
    }};
    Eigen::Vector2f path = pathfinding.front();
};
