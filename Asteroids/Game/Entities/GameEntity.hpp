#pragma once

#include "Engine/Entities/Entity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class GameEntity : public Entity {
public:
    void collisionCheck(Entity& entity);
    Eigen::AlignedBox2f getBounds() const override;
    virtual void render(SDL_Renderer& renderer) override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
protected:
    GameEntity() = default;
        
    Eigen::Vector2f velocity = Eigen::Vector2f::Zero();
};
