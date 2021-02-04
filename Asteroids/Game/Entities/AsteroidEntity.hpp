#pragma once

#include "Engine/Entities/GameEntity.hpp"
#include <SDL.h>

class AsteroidEntity : public GameEntity {
public:
    enum class AsteroidStage {
        STAGE_1 = 0,
        STAGE_2 = 1,
        STAGE_LAST
    };
    
    AsteroidEntity(AsteroidStage stage = AsteroidStage::STAGE_1);
    
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    const AsteroidStage stage;
    int speed = 50;
};
