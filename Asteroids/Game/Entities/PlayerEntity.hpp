#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <Eigen/Dense>

class PlayerEntity : public Entity {
public:
    PlayerEntity();
    virtual void render(SDL_Renderer& renderer) override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
    virtual void update(const SDL_Event& event) override;
    virtual void update(float deltaTime) override;
private:
    const float acceleration = 7.5f;
    const float maxSpeed = 475.f;
};
