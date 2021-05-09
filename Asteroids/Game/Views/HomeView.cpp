#include "Engine/Managers/GameManager.hpp"
#include "Game/ManagerHelper.hpp"
#include "Game/Entities/PlayerEntity.hpp"
#include "Game/Views/HomeView.hpp"

void HomeView::render(SDL_Renderer& renderer) {
    
}

void HomeView::update(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            if(event.key.keysym.sym == SDLK_RETURN) {
                break;
            }
        }
    }
}
