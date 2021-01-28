#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <string>

class RenderComponent;
class Entity;

class Component {
public:
    virtual ~Component();

    virtual void render(SDL_Renderer& renderer);
    
    bool getIsVisible();
    void setOwnerEntity(Entity* entityOwner);
    void setIsVisible(bool isVisible); 
    std::string name = "";

protected:
    Component() = default;
    
    virtual RenderComponent* getRenderComponent();

    bool isEnabled = true;
    Entity* ownerEntity = nullptr;
private:
    RenderComponent* renderComponent = nullptr;
};
