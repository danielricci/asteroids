#pragma once

#include "Engine/Managers/Manager.hpp"

class UIManager : public Manager {
public:
    UIManager(SDL_Renderer& renderer);
    virtual void processEvent(const SDL_Event& event) override;
    
    SDL_Renderer& getRenderer() { return renderer; }
private:
    SDL_Renderer& renderer;
};
