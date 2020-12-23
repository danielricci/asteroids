#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class GameEntity : public Entity {
public:
    virtual void collision(Entity& entity) override;
    virtual void setPosition(const Eigen::Vector2f& position) override;
protected:
    GameEntity() = default;
};
