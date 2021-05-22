#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>
#include <SDL.h>

class View : public Entity {
public:
    virtual ~View();
    virtual void render(SDL_Renderer& renderer);
    
    virtual void onViewActivated();
protected:
    std::vector<Entity*> entities;
public:
    virtual std::string getViewName() const = 0;
};
