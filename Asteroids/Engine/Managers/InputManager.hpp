#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/Manager.hpp"

#include <SDL.h>

#include <list>

class InputManager : public Manager {
public:
    InputManager();
    ~InputManager();
    virtual void processEvent(const SDL_Event& event) override;
private:
    SDL_GameController* gameController = nullptr;
};
