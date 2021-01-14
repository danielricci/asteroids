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
    
    void handleCollision();
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    
    void setGameState(GameManager::GameState gameState);
    GameManager::GameState getGameState() const;
    
    void stopGame();
    void startGame();
    void pauseGame();
private:
    GameState gameState = GameState::STOPPED;
};
