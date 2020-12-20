#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>

class PhysicsComponent : public Component {
public:
    std::function<void()> eventOnCollide = nullptr;
    bool collide(const Entity& entity) const;
};
