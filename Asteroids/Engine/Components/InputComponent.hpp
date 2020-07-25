#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <unordered_map>
#include <string>

class InputComponent : public Component {

public:
    InputComponent() = default;
    
    void addBinding(SDL_Keycode keyCode, const std::string& action);
    void addBinding(SDL_Keycode keyCode, const std::string& action, std::function<void(const SDL_Event&)> functor);
    void addBinding(SDL_GameControllerAxis axis, const std::string& action);
    void addBinding(SDL_GameControllerAxis axis, const std::string& action, std::function<void(const SDL_Event&)> functor);
    void registerActionBinding(const std::string& action, std::function<void(const SDL_Event&)> functor);
    void update(const SDL_Event& event);
    
protected:
    virtual int getDeadZone() const;
    
private:
    typedef std::unordered_multimap<SDL_Keycode, std::string> InputBindingsMap;
    InputBindingsMap inputBindings;
    
    typedef std::unordered_map<std::string, std::function<void(const SDL_Event&)>> ActionBindingsMap;
    ActionBindingsMap actionBindings;
};
