#include "Game/Components/PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent() {
    this->addBinding(SDLK_LEFT, std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_RIGHT, std::bind(&PlayerInputComponent::onRotate, this, std::placeholders::_1));
    this->addBinding(SDLK_UP, std::bind(&PlayerInputComponent::onThrust, this, std::placeholders::_1));
    this->addBinding(SDLK_RSHIFT, std::bind(&PlayerInputComponent::onHyperspace, this, std::placeholders::_1));
    this->addBinding(SDLK_SPACE, std::bind(&PlayerInputComponent::onShoot, this, std::placeholders::_1));
}

void PlayerInputComponent::onRotate(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT: {
                    rotationAction = RotationAction::ROTATE_LEFT;
                    break;
                }
                case SDLK_RIGHT: {
                    rotationAction = RotationAction::ROTATE_RIGHT;
                    break;
                }
            }
            break;
        case SDL_KEYUP: {
            rotationAction = RotationAction::NONE;
            break;
        }
    }
}

void PlayerInputComponent::onThrust(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYDOWN: {
            if(!isThrustActivated) {
                isThrustActivated = true;
                if(eventOnThrustStart != nullptr) {
                    eventOnThrustStart();
                }
            }
            break;
        }
        case SDL_KEYUP: {
            if(isThrustActivated) {
                isThrustActivated = false;
                if(eventOnThrustStop != nullptr) {
                    eventOnThrustStop();
                }
            }
            break;
        }
    }
}

void PlayerInputComponent::onHyperspace(const SDL_Event& event) {
    switch(event.type) {
        case SDL_KEYUP: {
            isThrustActivated = false;
            if(eventOnHyperspace != nullptr) {
                eventOnHyperspace();
            }
            break;
        }
    }
}

void PlayerInputComponent::onShoot(const SDL_Event& event) {
    if(event.type == SDL_KEYUP && eventOnShoot != nullptr) {
        eventOnShoot();
    }
}
