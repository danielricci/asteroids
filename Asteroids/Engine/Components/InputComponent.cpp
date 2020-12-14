#include "Engine/Components/InputComponent.hpp"

void InputComponent::addBinding(SDL_Keycode keyCode, std::function<void(const SDL_Event&)> functor) {
    inputBindings.emplace(keyCode, functor);
}

void InputComponent::addBinding(SDL_GameControllerAxis axis, std::function<void(const SDL_Event&)> functor) {
    inputBindings.emplace(axis, functor);
}

void InputComponent::update(const SDL_Event& event) {
    InputBindings::const_iterator inputIterator = inputBindings.find(event.key.keysym.sym);
    if(inputIterator == inputBindings.end()) {
        inputIterator = inputBindings.find(event.caxis.axis);
    }
    if(inputIterator != inputBindings.end()) {
        auto functor = inputIterator->second;
        if(functor != nullptr) {
            functor(event);
        }
    }
}

int InputComponent::getDeadZone() const {
    return 8000;
}
