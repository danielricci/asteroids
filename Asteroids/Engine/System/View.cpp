#include "Engine/System/View.hpp"

void View::render(SDL_Renderer& renderer) {
    if(isVisible) {
        for(Entity* entity : entities) {
            if(entity != nullptr) {
                entity->render(renderer);
            }
        }
    }
}
