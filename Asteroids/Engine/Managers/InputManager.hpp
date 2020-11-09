#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class InputManager : public Manager {
public:
    InputManager();
    virtual ~InputManager();
    
    virtual void update(const SDL_Event& event) override;
private:
    SDL_GameController* gameController = nullptr;
};
