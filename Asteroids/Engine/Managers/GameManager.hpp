#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class GameManager : public Manager {
public:
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    virtual void render(SDL_Renderer& renderer) override;
    
    void stopGame();
    bool isGameStopped() const;
    
    void startGame();
    bool isGameStarted() const;
    
    void pauseGame();
    bool isGamePaused() const;
private:
    enum class GameState : char {
        STOPPED,
        STARTED,
        PAUSED
    };

    GameState gameState = GameState::STOPPED;
};
