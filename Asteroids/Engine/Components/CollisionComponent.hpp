#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Entities/Entity.hpp"

class CollisionComponent : public Component {
public:
    bool isCollidedAABB(const Entity& entity) const;
};
