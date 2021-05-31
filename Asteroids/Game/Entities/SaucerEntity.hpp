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
    float timerBullet = 0.f;
    int speed = 200;
    std::queue<Eigen::Vector2f> waypoints;
    Eigen::Vector2f waypoint = Eigen::Vector2f::Zero();
};
