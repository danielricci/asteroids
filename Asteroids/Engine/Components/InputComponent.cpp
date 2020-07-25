#include "Engine/Components/InputComponent.hpp"

void InputComponent::addBinding(SDL_Keycode keyCode, const std::string& action) {
    inputBindings.emplace(keyCode, action);
}

void InputComponent::addBinding(SDL_Keycode keyCode, const std::string& action, std::function<void(const SDL_Event&)> functor) {
    addBinding(keyCode, action);
    registerActionBinding(action, functor);
}

void InputComponent::addBinding(SDL_GameControllerAxis axis, const std::string& action) {
    inputBindings.emplace(axis, action);
}

void InputComponent::addBinding(SDL_GameControllerAxis axis, const std::string& action, std::function<void(const SDL_Event&)> functor) {
    addBinding(axis, action);
    registerActionBinding(action, functor);
}

void InputComponent::update(const SDL_Event& event) {
    InputBindingsMap::const_iterator inputIterator = inputBindings.find(event.key.keysym.sym);
    if(inputIterator == inputBindings.end()) {
        inputIterator = inputBindings.find(event.caxis.axis);
    }
    
    if(inputIterator != inputBindings.end()) {
        ActionBindingsMap::const_iterator actionIterator = actionBindings.find(inputIterator->second);
        if(actionIterator != actionBindings.end()) {
            actionIterator->second(event);
        }
    }
}

void InputComponent::registerActionBinding(const std::string& action, std::function<void(const SDL_Event&)> functor) {
    actionBindings[action] = functor;
}

int InputComponent::getDeadZone() const {
    return 8000;
}
