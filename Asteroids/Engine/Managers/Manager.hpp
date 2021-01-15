#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/ManagerInformation.hpp"
#include <SDL.h>
#include <list>
#include <map>

class Manager {
public:
    virtual ~Manager();
    
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    std::list<Entity*> purgeEntities();
    
    virtual void render(SDL_Renderer& renderer);
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
protected:
    Manager() = default;
    std::map<Entity*, ManagerInformation> entities;
};
