#pragma once

#include "Engine/Managers/Manager.hpp"
#include "Game/Entities/MainMenuEntity.hpp"

class UIManager : public Manager {
public:
    UIManager() = default;
    virtual ~UIManager();
    virtual void update(const SDL_Event& event) override;
    virtual void render(SDL_Renderer& renderer) override;
private:
    MainMenuEntity* startMenuEntity = new MainMenuEntity();
};
