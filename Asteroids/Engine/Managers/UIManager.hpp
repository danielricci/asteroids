#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/Manager.hpp"
#include <SDL.h>
#include <list>

class UIManager : public Manager {
public:
    virtual ~UIManager();
    
    virtual void update(const SDL_Event& event) override;
    virtual void render(SDL_Renderer& renderer) override;
    
    void addUIElement(Entity* entity);
private:
    std::list<Entity*> entities;
};
