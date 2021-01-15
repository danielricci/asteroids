#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class GameManager final : public Manager {
public:
    enum class GameState : char {
        STOPPED,
        STARTED,
        PAUSED
    };
    
    GameManager::GameState getGameState() const;
    void handleCollision();
    virtual void render(SDL_Renderer& renderer) override;
    void setGameState(GameManager::GameState gameState);
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
private:
    GameState gameState = GameState::STOPPED;
};
