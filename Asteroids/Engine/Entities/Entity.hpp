#pragma once

#include "Engine/System/Node.hpp"
#include <SDL.h>

class Entity : public Node {
public:
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
protected:
    Entity();
};
