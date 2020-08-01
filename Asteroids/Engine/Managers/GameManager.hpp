#pragma once

#include "Engine/Entities/Entity.hpp"
#include "Engine/Managers/Manager.hpp"
#include <SDL.h>
#include <list>

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
    
    void addEntity(Entity* entity);
private:
    enum class GameState : char {
        STOPPED,
        STARTED,
        PAUSED
    };

    GameState gameState = GameState::STOPPED;
    
    std::list<Entity*> entities;
};
