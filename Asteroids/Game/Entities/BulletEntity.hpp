#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class BulletEntity : public
GameEntity {
public:
    BulletEntity();
    virtual Eigen::Vector2f getDimensions() const override;
    virtual void update(float deltaTime) override;
private:
    const int SPEED = 925;
    const int MAX_DISTANCE = 600;

    float timeTravelled = 0;
};

