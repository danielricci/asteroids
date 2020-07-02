#include "Engine/Managers/UIManager.hpp"

//#include <iostream>

UIManager::UIManager(SDL_Renderer& renderer) : renderer(renderer) {
}

void UIManager::processEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_MOUSEMOTION:
            //SDL_MouseMotionEvent event = event.motion;
            //std::cout << "SDL_MouseMotionEvent" << std::endl;
            break;
    }
}
