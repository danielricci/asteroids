#include "Engine/Managers/UIManager.hpp"
#include <SDL_ttf.h>
#include <iostream>

UIManager::UIManager() {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
}

UIManager::~UIManager() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();
    TTF_Quit();
}

void UIManager::render(SDL_Renderer& renderer) {
    for(Entity* entity : entities) {
        entity->render(renderer);
    }
}

void UIManager::update(float deltaTime) {
    for(Entity* entity : entities) {
        entity->update(deltaTime);
    }
}

void UIManager::update(const SDL_Event& event) {
    for(Entity* entity : entities) {
        entity->update(event);
    }
}
