#include "Game/Components/PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent() {
    this->addBinding(SDLK_LEFT, "ROTATE", std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, "ROTATE", std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    
}

void PlayerInputComponent::onRotate(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT: {
                        this->playerAction = PlayerAction::ROTATE_LEFT;
                        break;
                }
                case SDLK_RIGHT: {
                        this->playerAction = PlayerAction::ROTATE_RIGHT;
                        break;
                }
            }
            break;
        case SDL_KEYUP: {
            this->playerAction = PlayerAction::NONE;
            break;
        }
    }
}

PlayerInputComponent::PlayerAction PlayerInputComponent::getPlayerAction() const {
    return this->playerAction;
}
