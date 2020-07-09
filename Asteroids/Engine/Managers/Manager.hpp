#pragma once

#include <SDL.h>

class Manager {
public:
    virtual ~Manager() {
    }
    virtual void update(const SDL_Event& event) = 0;
    virtual void render(SDL_Renderer& renderer) = 0;
protected:
};
