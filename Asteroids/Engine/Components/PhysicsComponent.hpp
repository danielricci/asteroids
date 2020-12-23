#pragma once

#include "Engine/Components/Component.hpp"
#include "Engine/Components/RenderComponent.hpp"
#include <SDL.h>

class PhysicsComponent : public Component {
public:
    bool collide(const Entity& entity) const;
    virtual void render(SDL_Renderer& renderer);
    
    std::function<void()> eventOnCollide = nullptr;
};
