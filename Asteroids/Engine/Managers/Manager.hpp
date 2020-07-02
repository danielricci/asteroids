#pragma once

#include <SDL.h>

class Manager {
public:
    virtual ~Manager() {
    }
    virtual void processEvent(const SDL_Event& event) = 0;
protected:
};
