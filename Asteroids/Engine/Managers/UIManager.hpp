#pragma once

#include "Engine/Managers/Manager.hpp"
#include "Game/Entities/StartMenuEntity.hpp"

class UIManager : public Manager {
public:
    UIManager(SDL_Renderer& renderer);
    virtual ~UIManager();
    virtual void processEvent(const SDL_Event& event) override;

    SDL_Renderer& renderer;
    StartMenuEntity* startMenuEntity = new StartMenuEntity(renderer);
private:
};
