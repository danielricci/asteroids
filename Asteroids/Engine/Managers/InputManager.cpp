#include "Engine/Components/InputComponent.hpp"
#include "Engine/Managers/InputManager.hpp"

#include <iostream>

InputManager::InputManager() {
    if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL joystick initialization failed: " << SDL_GetError() << std::endl;
    }
    
    if(SDL_NumJoysticks() > 0) {
        gameController = SDL_GameControllerOpen(0);
        if(gameController == nullptr) {
            std::cerr << "Error opening the game controller " << SDL_GetError() << std::endl;
        }
    }
}

InputManager::~InputManager() {
    if(gameController != nullptr) {
        SDL_GameControllerClose(gameController);
        gameController = nullptr;
    }
    
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

void InputManager::processEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_CONTROLLERAXISMOTION: {
            if(gameController == nullptr) {
                break;
            }
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
//            for(Entity* entity : entities) {
//                if(entity != nullptr) {
//                    entity->getComponent<InputComponent>()->processEvent(event);
//                }
//            }
            break;
        }
    }
}
