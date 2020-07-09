#pragma once

#include "Engine/Components/Component.hpp"

#include <SDL.h>

#include <unordered_map>
#include <string>

class InputComponent : public Component {

public:
    InputComponent() = default;
    
    void addBinding(SDL_Keycode keyCode, const std::string& action) {
        inputBindings.emplace(keyCode, action);
    }

    void addBinding(SDL_Keycode keyCode, const std::string& action, std::function<void(const SDL_Event&)> functor) {
        addBinding(keyCode, action);
        registerActionBinding(action, functor);
    }
    
    void addBinding(SDL_GameControllerAxis axis, const std::string& action) {
        inputBindings.emplace(axis, action);
    }

    void addBinding(SDL_GameControllerAxis axis, const std::string& action, std::function<void(const SDL_Event&)> functor) {
        addBinding(axis, action);
        registerActionBinding(action, functor);
    }
    
    void update(const SDL_Event& event) {
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

    void registerActionBinding(const std::string& action, std::function<void(const SDL_Event&)> functor) {
        actionBindings[action] = functor;
    }
    
protected:
    virtual int getDeadZone() const {
        return 8000;
    }
    
private:
    typedef std::unordered_multimap<SDL_Keycode, std::string> InputBindingsMap;
    InputBindingsMap inputBindings;
    
    typedef std::unordered_map<std::string, std::function<void(const SDL_Event&)>> ActionBindingsMap;
    ActionBindingsMap actionBindings;
};
