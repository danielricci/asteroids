#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>
#include <SDL.h>

class View : public Entity {
public:
    virtual ~View();
    virtual void render(SDL_Renderer& renderer);
protected:
    std::vector<Entity*> entities;
public:
    bool isVisible = false;
    virtual std::string getViewName() const = 0;
};
