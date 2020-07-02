#pragma once

#include "Engine/Components/TextComponent.hpp"
#include "Engine/Entities/Entity.hpp"

#include <string>

class MenuItem : public Entity {
protected:
    MenuItem(int size, std::string text);
    virtual ~MenuItem() = default;
    
    virtual void onEntered() = 0;
    virtual void onExited() = 0;
    virtual void onExecute() = 0;
};
