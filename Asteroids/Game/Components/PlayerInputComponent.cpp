#include "Game/Components/PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent() {
    this->addBinding(SDLK_LEFT, "ROTATE_LEFT", std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, "ROTATE_RIGHT", std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_UP, "THRUST", std::bind(&PlayerInputComponent::onThrust, this, std::placeholders::_1));
    this->addBinding(SDLK_RSHIFT, "HYPERSPACE", std::bind(&PlayerInputComponent::onHyperspace, this, std::placeholders::_1));
    this->addBinding(SDLK_LSHIFT, "HYPERSPACE", std::bind(&PlayerInputComponent::onHyperspace, this, std::placeholders::_1));
    this->addBinding(SDLK_SPACE, "SHOOT", std::bind(&PlayerInputComponent::onShoot, this, std::placeholders::_1));
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
