#include "Engine/System/View.hpp"

View::~View() {
    isVisible = false;
    
    for(Entity* entity : entities) {
        if(entity != nullptr) {
            delete entity;
        }
    }
    
    entities.clear();
}

void View::render(SDL_Renderer& renderer) {
    if(isVisible) {
        for(Entity* entity : entities) {
            if(entity != nullptr) {
                entity->render(renderer);
            }
        }
    }
}
