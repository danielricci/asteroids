#include "Engine/Managers/UIManager.hpp"
#include <SDL_ttf.h>
#include <iostream>

UIManager::UIManager() {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
}

UIManager::~UIManager() {
    TTF_Quit();
}
