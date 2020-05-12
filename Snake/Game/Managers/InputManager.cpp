/**
* MIT License
*
* Copyright (c) 2020 Daniel Ricci {@literal <thedanny09@icloud.com>}
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "Game/Managers/InputManager.hpp"

#include <iostream>

InputManager::InputManager() {
    if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL joystick initialization failed: " << SDL_GetError() << std::endl;
    }
    
    // Note: For now the first joystick is the one that is used
    if(SDL_NumJoysticks() > 0) {
        gameController = SDL_GameControllerOpen(0);
        if(gameController == nullptr) {
            std::cerr << "Error opening the game controller " << SDL_GetError() << std::endl;
        }
    }
}

InputManager::~InputManager() {
    terminate();
}

void InputManager::process(const SDL_Event& event, const std::list<InputComponent*>& inputComponents) const {
    switch(event.type) {
        case SDL_CONTROLLERAXISMOTION: {
            if(gameController == nullptr) {
                break;
            }
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            for(InputComponent* inputComponent : inputComponents) {
                if(inputComponent != nullptr) {
                    inputComponent->handleEvent(event);
                }
            }
            break;
        }
    }
}

void InputManager::terminate() {
    if(gameController != nullptr) {
        SDL_GameControllerClose(gameController);
        gameController = nullptr;
    }
    
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}
