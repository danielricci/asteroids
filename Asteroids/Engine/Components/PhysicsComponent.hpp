#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include "Engine/System/EventArgs.hpp"
#include "Engine/System/EventHandler.hpp"

class PhysicsComponent : public Component {
public:
    bool isCollidedWith(const Entity& entity) const;
    EventHandler<EventArgs> eventOnCollide;
};
