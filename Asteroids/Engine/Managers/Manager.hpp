#pragma once

#include "Engine/Entities/Entity.hpp"
#include <SDL.h>
#include <list>

class Manager {
public:
    Manager() = default;
    virtual ~Manager() = default;
    
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    virtual void render(SDL_Renderer& renderer);
    
    void addEntity(Entity* entity);
protected:
    std::list<Entity*> entities;
};
