#pragma once

#include "Engine/Managers/Manager.hpp"
#include <SDL.h>

class GameManager final : public Manager {
public:
    GameManager() = default;
    
    enum class GameState : char {
        STOPPED,
        STARTED,
        PAUSED
    };
    
    GameManager::GameState getGameState() const;
    
    void handleCollision();
    virtual void initialize() override;
    void setGameState(GameManager::GameState gameState);
    virtual void update(float deltaTime) override;
    virtual void update(const SDL_Event& event) override;
    
    template<typename T> T* get() {
        for(auto& pair : entities) {
            T* object = dynamic_cast<T*>(pair.first);
            if(object != nullptr) {
                return object;
            }
        }
       
        return nullptr;
    }
private:
    GameState gameState = GameState::STOPPED;
};
