#pragma once

#include "Engine/Entities/Entity.hpp"
#include <vector>

class View : Entity {
public:
    virtual void render(SDL_Renderer& renderer) override;
protected:
    std::vector<Entity*> entities;
    bool isVisible = true;
};
