#include "Game/Components/PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent() {
    this->addBinding(SDLK_LEFT, EVENT_ROTATE_LEFT, std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, EVENT_ROTATE_RIGHT, std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_UP, EVENT_THRUST, std::bind(&PlayerInputComponent::onThrust, this, std::placeholders::_1));
    
    // TODO - hyperspace can be bound directly, no need for its own method
    //this->addBinding(SDLK_RSHIFT, EVENT_HYPERSPACE, std::bind(&PlayerInputComponent::onHyperspace, this, std::placeholders::_1));
    //this->addBinding(SDLK_LSHIFT, EVENT_HYPERSPACE, std::bind(&PlayerInputComponent::onHyperspace, this, std::placeholders::_1));
    this->addBinding(SDLK_LSHIFT, EVENT_HYPERSPACE);
    this->addBinding(SDLK_RSHIFT, EVENT_HYPERSPACE);
    this->addBinding(SDLK_SPACE, EVENT_SHOOT);
}

void PlayerInputComponent::onRotate(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT: {
                    this->rotationAction = PlayerAction::ROTATE_LEFT;
                    break;
                }
                case SDLK_RIGHT: {
                    this->rotationAction = PlayerAction::ROTATE_RIGHT;
                    break;
                }
            }
            break;
        case SDL_KEYUP: {
            this->rotationAction = PlayerAction::NONE;
            break;
        }
    }
}

void PlayerInputComponent::onThrust(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN: {
            this->movementAction = PlayerAction::THRUST;
            break;
        }
        case SDL_KEYUP: {
            this->movementAction = PlayerAction::NONE;
            break;
        }
    }
}

void PlayerInputComponent::onHyperspace(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            this->movementAction = PlayerAction::HYPERSPACE;
            break;
        }
    }
}

void PlayerInputComponent::onShoot(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            SDL_UserEvent userEvent;
            userEvent.type = SDL_USEREVENT;
            userEvent.code = 100;
            SDL_Event thisEvent;
            thisEvent.type = SDL_USEREVENT;
            thisEvent.user = userEvent;
            SDL_PushEvent(&thisEvent);
            break;
        }
    }
}

PlayerInputComponent::PlayerAction PlayerInputComponent::getRotationAction() const {
    return this->rotationAction;
}

PlayerInputComponent::PlayerAction PlayerInputComponent::getMovementAction() const {
    return this->movementAction;
}

void PlayerInputComponent::reset() {
    this->rotationAction = PlayerAction::NONE;
    this->movementAction = PlayerAction::NONE;
}
