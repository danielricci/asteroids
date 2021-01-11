#pragma once

#include "Game/Entities/GameEntity.hpp"
#include <Eigen/Dense>
#include <SDL.h>
#include <vector>

class SaucerEntity : public GameEntity {
public:
    SaucerEntity();
    
    virtual void render(SDL_Renderer& renderer) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    int speed = 65;
    const std::vector<std::vector<SDL_Point>> saucerParts = {{
        {{5, -5}, {10, -15}, {25, -15}, {30, -5}},
        {{0, 0}, {5, -5}, {30, -5}, {36, 1}},
        {{0, 0}, {5, 5}, {30, 5}, {35, 0}},
    }};
};
