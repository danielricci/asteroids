#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <array>
#include <vector>
#include <Eigen/Dense>

class AsteroidEntity : public Entity {
public:
    AsteroidEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
private:
    static const int speed = 40;
    static const int ASTEROID_KIND_COUNT = 4;
    const std::array<std::vector<SDL_Point>, AsteroidEntity::ASTEROID_KIND_COUNT> asteroidShapes = {{
        {{0, 0}, {30, 0}, {60, 30}, {60, 45}, {30, 60}, {60, 75}, {45, 90}, {30, 75}, {0, 90}, {-15, 60}, {-15, 30}, {15, 30}, {0, 0}}//,
        //{{10, 0}, {30, -20}, {50, 0},{30, 10},{50, 30},{40, 40},{20, 30},{0, 40},{-20, 20},{-10, 10},{-20, 0},{-10, -10},{10, 0}}
    }};
};
