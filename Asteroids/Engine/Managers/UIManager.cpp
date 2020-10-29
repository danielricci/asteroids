#include "Engine/Managers/UIManager.hpp"
#include <SDL_ttf.h>
#include <iostream>

UIManager::UIManager() {
    if(TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not be initialized: " << TTF_GetError() << std::endl;
    }
}

UIManager::~UIManager() {
    for(Node* node : this->nodes) {
        if(node != nullptr) {
            delete node;
            node = nullptr;
        }
    }
    this->nodes.clear();
    TTF_Quit();
}

void UIManager::render(SDL_Renderer& renderer) {
    for(Node* node : this->nodes) {
        if(node != nullptr) {
            Entity* entity = dynamic_cast<Entity*>(node);
            if(entity != nullptr) {
                entity->render(renderer);
            }
        }
    }
}

void UIManager::update(float deltaTime) {
    for(Node* node : this->nodes) {
        if(node != nullptr) {
            Entity* entity = dynamic_cast<Entity*>(node);
            if(entity != nullptr) {
                entity->update(deltaTime);
            }
        }
    }
}

void UIManager::update(const SDL_Event& event) {
    for(Node* node : this->nodes) {
        if(node != nullptr) {
            Entity* entity = dynamic_cast<Entity*>(node);
            if(entity != nullptr) {
                entity->update(event);
            }
        }
    }
}
