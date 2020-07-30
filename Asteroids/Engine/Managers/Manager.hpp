#pragma once

#include <SDL.h>

class Manager {
public:
    virtual ~Manager() = default;
    
    virtual void update(float deltaTime) = 0;
    virtual void update(const SDL_Event& event) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;
};
