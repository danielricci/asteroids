#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <vector>

class AsteroidEntity : public GameEntity {
public:
    enum class AsteroidStage {
        STAGE_1 = 0,
        STAGE_2 = 1,
        STAGE_LAST
    };
    
    AsteroidEntity(AsteroidStage stage = AsteroidStage::STAGE_1);
    
    virtual SDL_Rect getEntityBounds() const override;
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    const AsteroidStage stage;
    int speed = 50;
    const std::vector<std::vector<SDL_Point>> asteroidShapes = {{
        {{0, 0}, {30, 0}, {60, 30}, {60, 45}, {30, 60}, {60, 75}, {45, 90}, {30, 75}, {0, 90}, {-15, 60}, {-15, 30}, {15, 30}, {0, 0}},
        {{0, 0}, {20, 0}, {40, 20}, {40, 30}, {20, 40}, {40, 50}, {30, 60}, {20, 50}, {0, 60}, {-10, 40}, {-10, 20}, {10, 20}, {0, 0}},
        {{0, 0}, {10, 0}, {20, 10}, {20, 15}, {10, 20}, {20, 25}, {15, 30}, {10, 25}, {0, 30}, {-5, 20}, {-5, 10}, {5, 10}, {0, 0}}
    }};
};
