
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
    void clean(Entity* entity);
    std::list<Entity*> flush();
    virtual void render(SDL_Renderer& renderer);
    virtual void update(float deltaTime);
    virtual void update(const SDL_Event& event);
    
protected:
    Manager() = default;
private:
    std::map<Entity*, ManagerInformation> entitiesMap;
};
