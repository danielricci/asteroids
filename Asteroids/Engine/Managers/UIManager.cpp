
#include "Engine/Managers/UIManager.hpp"
#include "Game/Entities/CopyrightEntity.hpp"
#include "Game/Entities/GameOverEntity.hpp"
#include "Game/Entities/HighScoreEntity.hpp"
#include "Game/Entities/LivesEntity.hpp"
#include "Game/Entities/PlayerScoreEntity.hpp"
#include <iostream>
#include <SDL_ttf.h>

UIManager::UIManager() {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
    
    initialize();
}

UIManager::~UIManager() {
    TTF_Quit();
}

void UIManager::initialize() {  
    addEntity(new GameOverEntity());
    addEntity(new HighScoreEntity());
    addEntity(new LivesEntity());
    addEntity(new PlayerScoreEntity());
    addEntity(new CopyrightEntity());
}
