#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class InputManager final : public Manager {
public:
    InputManager();
    virtual ~InputManager();
private:
    SDL_GameController* gameController = nullptr;
};
