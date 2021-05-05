#include "Engine/Managers/ViewManager.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include <iostream>
#include <SDL_ttf.h>

ViewManager::ViewManager(const std::initializer_list<View*>& views) {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
    
    for(auto& view : views) {
        this->views.push_back(view);
    }
}

ViewManager::~ViewManager() {
    // Hack: Prevent the base class from having anything to clear, TTF_QUIT must be called last
    clean();
    TTF_Quit();
}

// TODO: no longer needed
void ViewManager::initialize() {  
    addEntity(new CopyrightEntity());
    addEntity(new GameOverEntity());
    addEntity(new HighScoreEntity());
    addEntity(new LivesEntity());
    addEntity(new PlayerScoreEntity());
}
