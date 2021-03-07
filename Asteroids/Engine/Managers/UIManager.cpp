#include "Engine/Managers/UIManager.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include <SDL_ttf.h>
#include <iostream>

UIManager::UIManager() {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
    
    addEntity(new HighScoreEntity());
    addEntity(new LivesEntity());
    addEntity(new PlayerScoreEntity());
}

UIManager::~UIManager() {
    TTF_Quit();
}
