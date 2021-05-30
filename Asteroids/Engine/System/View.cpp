#include "Engine/Components/Component.hpp"
#include "Engine/System/View.hpp"

std::vector<Entity*> View::shared_entities;


View::~View() {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
        }
    }
    
    entities.clear();
    
    for(Entity* entity : shared_entities) {
        if(entity != nullptr) {
            delete entity;
        }
    }
    
    shared_entities.clear();
}

void View::render(SDL_Renderer& renderer) {
    for(Entity* entity : shared_entities) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->render(renderer);
        }
    }
    for(Component* component : getComponents()) {
        component->render(renderer);
    }
}

void View::update(float deltaTime) {
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->update(deltaTime);
        }
    }
}

void View::update(const SDL_Event& event) {
    for(Entity* entity : shared_entities) {
        if(entity != nullptr) {
            entity->update(event);
        }
    }
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            entity->update(event);
        }
    }
}

void View::onViewActivated() {
}
