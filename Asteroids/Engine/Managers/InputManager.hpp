#pragma once

#include "Engine/Components/InputComponent.hpp"

#include <SDL.h>

#include <list>

class InputManager {
public:
    ~InputManager();

    static InputManager* getInstance() {
        static InputManager* instance = new InputManager();
        return instance;
    }
    void process(const SDL_Event& event, const std::list<InputComponent*>& inputComponents) const;
private:
    InputManager();
    SDL_GameController* gameController { nullptr };
};
