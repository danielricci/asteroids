#pragma once

#include "Engine/Components/TextComponent.hpp"
#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <string>

class MenuEntity : public Entity {
public:
    virtual void update(const SDL_Event& event) override final {
        // TODO - When the message comes here, its the job of this guy to call the
        //        proper onEntered, onExited, onExecute method, and also there should be flags
        //        here that get set so that it knows when it has already entered, and already exited
    }
protected:
    MenuEntity() = default;
    virtual ~MenuEntity() = default;
    
    virtual void onEntered() = 0;
    virtual void onExited() = 0;
    virtual void onExecute() = 0;
};
