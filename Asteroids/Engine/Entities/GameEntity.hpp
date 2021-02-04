#pragma once

#include "Engine/Entities/Entity.hpp"
#include <Eigen/Dense>
#include <SDL.h>

class GameEntity : public Entity {
public:
    // Note: I dont like the fact that collision detection forces us to have
    //       lingering functions in the event that some entity would have a
    //       physics component
    virtual void collisionCheck(Entity& entity) override final;
    virtual Eigen::AlignedBox2f getBounds() const override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
protected:
    GameEntity() = default;
    Eigen::Vector2f velocity = Eigen::Vector2f::Zero();
};
