#pragma once

#include "Engine/Entities/GameEntity.hpp"

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
    int speed = 120;
};
