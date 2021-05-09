#include "Engine/Managers/ViewManager.hpp"
#include <iostream>
#include <SDL_ttf.h>

ViewManager::ViewManager(const std::initializer_list<View*>& views) {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
    
    for(auto& view : views) {
        this->addEntity(view);
    }
}

ViewManager::~ViewManager() {
    // Hack: Prevent the base class from having anything to clear, TTF_QUIT must be called last
    clean();
    TTF_Quit();
}


