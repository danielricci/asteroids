#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <array>
#include <vector>
#include <Eigen/Dense>

class AsteroidEntity : public Entity {
public:
    enum class AsteroidSize {
        BIG = 0,
        SMALL
    };
    
    AsteroidEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
    void setAsteroidSize(const AsteroidSize& asteroidSize);
private:
    AsteroidSize asteroidSize = AsteroidSize::BIG;
    static const int speed = 40;
    static const int ASTEROID_KIND_COUNT = 1;
    const std::array<std::vector<SDL_Point>, AsteroidEntity::ASTEROID_KIND_COUNT> asteroidShapes = {{
        {{0, 0}, {30, 0}, {60, 30}, {60, 45}, {30, 60}, {60, 75}, {45, 90}, {30, 75}, {0, 90}, {-15, 60}, {-15, 30}, {15, 30}, {0, 0}}
    }};
};
