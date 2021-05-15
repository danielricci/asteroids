#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>
#include <SDL.h>

class View : public Entity {
public:
    virtual ~View();
    virtual void render(SDL_Renderer& renderer);
    
    bool getIsVisible() const {
        return isVisible;
    }
protected:
    std::vector<Entity*> entities;
    bool isVisible = false;
};
