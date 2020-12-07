#include "Engine/Managers/Manager.hpp"

Manager::~Manager() {
    clearEntities();
}

void Manager::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void Manager::clearEntities() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
        }
    }
    entities.clear();
}

void Manager::update(float deltaTime) {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->update(deltaTime);
        }
    }
}

void Manager::update(const SDL_Event& event) {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->update(event);
        }
    }
}

void Manager::render(SDL_Renderer& renderer) {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
}
