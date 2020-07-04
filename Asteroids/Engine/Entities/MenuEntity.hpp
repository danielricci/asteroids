#pragma once

#include "Engine/Components/TextComponent.hpp"
#include "Engine/Entities/Entity.hpp"

#include <string>

class MenuEntity : public Entity {
protected:
    MenuEntity(int size, std::string text);
    virtual ~MenuEntity() = default;
    
    virtual void onEntered() = 0;
    virtual void onExited() = 0;
    virtual void onExecute() = 0;
private:
    
};
