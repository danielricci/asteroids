#pragma once

#include "Engine/Components/Component.hpp"
#include <SDL.h>
#include <unordered_map>

class InputComponent : public Component {

public:
    InputComponent() = default;
    void update(const SDL_Event& event);
    
protected:
    virtual int getDeadZone() const;
    
    void addBinding(SDL_Keycode keyCode, std::function<void(const SDL_Event&)> functor);
    void addBinding(SDL_GameControllerAxis axis, std::function<void(const SDL_Event&)> functor);
    
private:
    typedef std::unordered_multimap<SDL_Keycode, std::function<void(const SDL_Event&)>> InputBindings;
    InputBindings inputBindings;
};
