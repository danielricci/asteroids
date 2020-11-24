#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Entities/Entity.hpp"
#include <SDL.h>

class CollisionComponent : public Component {
public:
    CollisionComponent();
    bool isCollidedAABB(const Entity& entity) const;
    bool isValidCollision();
private:
    SDL_Rect rectangle;
};
