#pragma once

#include "Engine/System/EventArgs.hpp"
#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>

class AsteroidEntity : public GameEntity {
public:
    enum class AsteroidStage {
        STAGE_1 = 1,
        STAGE_2 = 2,
        STAGE_LAST = 3
    };
    
    AsteroidEntity(AsteroidStage stage = AsteroidStage::STAGE_1);
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void update(float deltaTime) override;
    
    const AsteroidStage stage;
private:
    void onEventCollide(Entity* sender, EventArgs args);
    
    int speed = 30;
};
