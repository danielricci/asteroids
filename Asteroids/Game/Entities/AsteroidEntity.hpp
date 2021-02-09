#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>
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
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    
    const AsteroidStage stage;
private:
    int speed = 50;
};
