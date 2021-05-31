#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class BulletEntity : public GameEntity {
public:
    BulletEntity(GameEntity* owner);
    virtual Eigen::Vector2f getDimensions() const override;
    virtual void update(float deltaTime) override;
    
    const bool fromPlayer = false;
private:
    const unsigned long long int ownerId;
    
    const int MAX_DISTANCE = 600;
    const int SPEED = 925;
    float timeTravelled = 0;
};

