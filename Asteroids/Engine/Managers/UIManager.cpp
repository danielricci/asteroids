#include "Engine/Managers/UIManager.hpp"

UIManager::~UIManager() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.clear();
}

void UIManager::render(SDL_Renderer& renderer) {
    for(Entity* entity : entities) {
        entity->render(renderer);
    }
}

void UIManager::update(const SDL_Event& event) {
    for(Entity* entity : entities) {
        entity->update(event);
    }
}

void UIManager::addUIElement(Entity* entity) {
    this->entities.push_back(entity);
}
