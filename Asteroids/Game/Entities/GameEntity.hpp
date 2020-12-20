#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class GameEntity : public Entity {
public:
    virtual void setPosition(const Eigen::Vector2f& position) override;
    virtual void collision(Entity& entity) override;
protected:
    GameEntity() = default;
};
