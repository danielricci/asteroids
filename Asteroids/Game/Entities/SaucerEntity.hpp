#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>

class SaucerEntity : public GameEntity {
public:
    SaucerEntity();
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void update(float deltaTime) override;
private:
    int speed = 65;
};
