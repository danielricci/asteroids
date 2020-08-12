#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class UIManager : public Manager {
public:
    UIManager();
    virtual ~UIManager();
    
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    virtual void render(SDL_Renderer& renderer) override;
};
